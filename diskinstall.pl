#!/usr/bin/env perl
# Disk Installer Script v1.0
# Copyright (c) 2011, Robert Schofield
# All rights reserved.

use warnings;

system("clear");
print( 
  "Disk Installer for the Alpha OS\n",
  "Version 1.0 Beta\n",
  "Must be running as root to install to a disk!\n\n",
  "Location of the disk to install to:\n",
  "For example: \"/dev/sdc\" \n",
  "> "
);
chomp($disklocation = <STDIN>);
print "Okay, you said: $disklocation\n";
&AreYouSure;

sub AreYouSure {
  print "Are you sure (y/n)? ";
  chomp($sure = <STDIN>);
  if (lc($sure) eq 'y') {
    system("dd if=build/boot.bin of=$disklocation bs=512 count=1");
    #system("dd if=build/boot2.bin of=$disklocation bs=512 count=2");
    print "Installed!\n";
  }
  elsif (lc($sure) eq 'n') { 
    print "Exiting.\n";
    exit(1);
  }
  else {
    print "You *must* say y for yes or n for no\n";
    &AreYouSure;
  }
};