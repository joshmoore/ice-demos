#!/usr/bin/env python
# **********************************************************************
#
# Copyright (c) 2003-2017 ZeroC, Inc. All rights reserved.
#
# **********************************************************************

import os
import subprocess
pid = os.getpid()

def detect_pipes():
    out = subprocess.check_output("lsof -p %d" % pid, shell=True).split("\n")
    pipes = [x for x in out if "pipe" in x]
    print "\n".join(pipes)
    return pipes

import sys, traceback, Ice

Ice.loadSlice('Printer.ice')
import Demo

def run():
    status = 0
    ice = None
    try:
        ic = Ice.initialize(sys.argv)
        base = ic.stringToProxy("SimplePrinter:default -h 127.0.0.1 -p 10000")

        printer = Demo.PrinterPrx.checkedCast(base)
        if not printer:
            raise RuntimeError("Invalid proxy")

        printer.printString("Hello World!")
        return printer
    except:
        traceback.print_exc()
        status = 1

    finally:
        try:
            ic.destroy()
        except:
            traceback.print_exc()
            status = 1

print "(A)", "=" * 20
print "Run official client..."
run()
print len(detect_pipes()), "pipe(s) found\n"

print "(B)", "=" * 20
print "Keep a reference to the proxy..."
printer = run()
print len(detect_pipes()), "pipe(s) found\n"
