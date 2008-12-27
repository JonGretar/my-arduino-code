#!/usr/bin/env ruby -wKU
SERIAL = "/dev/tty.usbserial-A60061eR"

exec "avrdude -p m168 -P #{SERIAL} -c stk500v1 -b 19200 -F -u -U flash:w:#{ARGV[0]}.hex"