#!/usr/bin/perl
use strict;
use Dash::Connection;

my $dc = new Dash::Connection;
$dc->init({
	PeerAddr 	=> 'localhost',
	PeerPort	=> 33000,
	Timeout		=> 60,
});

my $rc = $dc->put({ key => 'test11', value => 'I have a dollar!' });

die "error with put command: " . $dc->error . "\n" if $rc < 1;

$rc = $dc->get({ key => 'test11' });

die "error getting key: " . $dc->error . "\n" if ! defined $rc;

print $rc . "\n";

