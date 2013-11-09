package Dash::ControlPort;

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

sub command {
    my ($self, $args) = @_;

    my $socket = $self->makeSocket;

    if (! $socket) {
        $self->error("socket is undefined.");

        return -1;
    }

    # read 'off' the prompt
    #

    my $select = new IO::Select($socket);

    my @readys = $select->can_read($self->timeout);

    if (! defined $readys[0]) {
        $self->error('timeout expired while reading prompt.');
        return undef;
    }

    my $junk;
    sysread $socket, $junk, 1024;

    # prep the command
    #

    @readys = $select->can_write($self->timeout);

    if (! defined $readys[0]) {
        $self->error('connection timed out before command.');
        return 0;
    }

    if (defined $readys[0]) {
        my $message = sprintf("%s\r\nexit\r\n", $args->{command});
        syswrite $socket, $message;
    }

    # read the response
    #

    @readys = $select->can_read($self->timeout);

    if (! defined $readys[0]) {
        $self->error('timeout expired after command. likely failed.');
        return -2;
    }

    my $response;

    my $read = 0;

    do {
        my $tempbuffer;
        $read = sysread $socket, $tempbuffer, 1024;
        $response .= $tempbuffer;
    } while ($read == 1024);

    close $socket;

    return $response;
}

sub keys {
    my ($self, $args) = @_;

    my @list;

    my $response = $self->command({ command => 'keys' });

    if ($response =~ /^unknown/) {
        $self->error($response);
        return undef;
    }
    
    foreach my $line (split /\n/, $response) {
        # TODO: make a hard-line rule against using whitespace as keys?

        $line =~ s/\s+$//;

        $line =~ s/^>$//;

        next if $line =~ /^$/;

        push @list, $line;
    }

    return \@list;
}

1;
