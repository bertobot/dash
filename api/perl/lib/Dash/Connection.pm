package Dash::Connection;

use strict;
use IO::Socket;
use IO::Select;

use Class::MethodMaker
[
        scalar  => 'error',

        scalar  => 'timeout',
        scalar  => 'host',
        scalar  => 'port',

        new     => 'new',
];

sub init {
    my ($self, $args) = @_;

    $self->timeout($args->{Timeout} );
    $self->host($args->{PeerAddr} );
    $self->port($args->{PeerPort} );
}

sub makeSocket {
    my ($self, $args) = @_;

    return new IO::Socket::INET(
        PeerAddr        => $self->host,
        PeerPort        => $self->port,
        Timeout         => $self->timeout,
        Proto           => 'tcp',
        Blocking        => 0,
    );


}

sub put {
    my ($self, $args) = @_;

    my $socket = $self->makeSocket;

    if (! $socket) {
        $self->error("socket is undefined.");

        return -1;
    }

    my $select = new IO::Select($socket);

    my @readys = $select->can_write($self->timeout);

    if (! defined $readys[0]) {
        $select->error('connection timed out before command.');
        return 0;
    }

    if (defined $readys[0]) {
        my $message = sprintf("put %s %s\r\n", $args->{key}, $args->{value});
        syswrite $socket, $message;
    }

    @readys = $select->can_read($self->timeout);

    if (! defined $readys[0]) {
        $select->error('timeout expired after command. likely failed.');
        return -2;
    }

    my $response = <$socket>;

    $response =~ s/\s+$//;

    if ($response eq "ok") {
        return length($args->{value});
    }

    $self->error('no response after transaction.');
    return -3;
}

sub get {
    my ($self, $args) = @_;

    my $socket = $self->makeSocket;

    if (! $socket) {
        $self->error("socket is undefined.");
        return undef;
    }

    my $select = new IO::Select($socket);

    my @readys = $select->can_write($self->timeout);

    if (! defined $readys[0]) {
        $select->error('connection timed out before command.');
        return undef;
    }

    if (defined $readys[0]) {
        my $message = sprintf("get %s\r\n", $args->{key});
        syswrite $socket, $message;
    }

    @readys = $select->can_read($self->timeout);

    if (! defined $readys[0]) {
        $select->error('timeout expired after command. likely failed.');
        return undef;
    }

    # first portion of response is the length of the result.

    my $response = '';
    my $length = 0;
    
    my $tbuffer;
    my $rc = 0;

    do {
        $rc = sysread($socket, $tbuffer, 1);
        $response .= $tbuffer;
    } while (defined $rc && $rc > 0 && $tbuffer =~ /\d/);

    $response =~ s/\s+$//;

    if ($response =~ /\d+/) {

        $length = $response;

        my $buffer;
        my $tempbuffer = '';
        my $rc = 0;

        

        while (1) {
            $rc = sysread($socket, $tempbuffer, $length);
            $buffer .= $tempbuffer;

            if (! defined $rc) {
                return undef;
            }

            if ($rc == 0 || $length == $rc) {
                last;
            }
        }

        # on a working case, function ends here
        return $buffer;
    }

    $self->error("received unexpected result: $response");
    return undef;
}

1;
