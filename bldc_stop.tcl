# Define hook procedures



grmon::execsh eval {
set timeStart -1
set Time [clock seconds]



set outfile [format "logg-%s.csv" $Time -format "%R"]
set fp0 -1
set cvarname ""

proc bldc_init {varname} {
	global fp0
	global outfile
	global cvarname
	global timeStart

	set timeStart [clock milliseconds]
	set cvarname $varname
	set fp0 [open $outfile w]

	puts "Logging to file $outfile"
	puts $fp0 "timestamp,timedelta"
}

proc timestamp {} {
	global timeStart
	global cvarname
	global fp0
	global timeStart
	set address [silent symbols lookup $cvarname]
	set tsdiff [silent mem $address 4]
	set timenow [clock milliseconds] 
	puts $fp0 "[format $tsdiff], [expr {$timenow - $timeStart}]"
}


proc bldc_close {} {
	global fp0
	close $fp0
}




proc old_timestamp {} {
    set outfile [open "myfile.txt" a+]
    set ts [mem 0x80002108 4] 
    puts $outfile "$ts"
    close $outfile
}

proc stop {} { 
    
    wmem 0x8000d018 0x00000000 0x00000000
    
}

proc start {} {
    wmem 0x8000d018 0xa0a0a0a0 0x0000a0a0
}
lappend ::hooks::postexec ::stop; # Add hooks
#lappend ::hooks::preexec ::start ;

#lappend ::hooks::preexec ::bldc_init varname; # Add hooks
#lappend ::hooks::postexec ::bldc_close;
lappend ::hooks::exec ::timestamp;
}

