#!/usr/bin/perl
use strict;

use lib 'api/perl/lib';
use lib 'lib/perl5';

use Dash::Connection;
use Getopt::Long;

my $opt_key;
my $opt_value;
my $opt_put;
my $opt_get;

my $options = GetOptions(
    "put"       => \$opt_put,
    "get"       => \$opt_get,
    "key=s"     => \$opt_key,
    "value=s"   => \$opt_value,
);

#if (! $opt_key || ! $opt_value) {
#    print "$0 --key <key> --value <value>\n";
#    exit 1;
#}

my $dc = new Dash::Connection;
$dc->init({
	PeerAddr 	=> 'localhost',
	PeerPort	=> 33000,
	Timeout		=> 60,
});

if ($opt_put) {
    my $rc = $dc->put({ 
        key     => $opt_key, 
        value   => $opt_value,
    });

    die "error with put command: " . $dc->error . "\n" if $rc < 1;
}

if ($opt_get) {
    my $rc = $dc->get({ 
        key     => $opt_key, 
    });


    #syswrite(STDOUT, $rc, length($rc) );
    printf "%s\n", $rc;
    


}


