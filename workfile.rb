#!/usr/bin/ruby

require File.expand_path(ENV['MOSYNCDIR']+'/rules/mosync_lib.rb')

mod = PipeLibWork.new
mod.instance_eval do
	def setup_native
		@LOCAL_DLLS = ["mosync", "mastd"]
		if(@GCC_IS_V4 && @GCC_V4_SUB >= 4)
			@EXTRA_CFLAGS = " -D_STDIO_H"
		end
		setup_base
	end
	
	def setup_pipe
		setup_base
	end
	
	def setup_base
		if(CONFIG == "")
			# broken compiler
			@SPECIFIC_CFLAGS = {"File.c" => " -Wno-unreachable-code"}
		else
			@SPECIFIC_CFLAGS = {}
		end
		#@SOURCES = ["libsupc++","src"]
		@SOURCES = ["."]
		@EXTRA_INCLUDES = ["."]
		@INSTALL_INCDIR = "ustl"
    #@EXTRA_CFLAGS += " -DHAVE_STDINT_H=1 -fno-exceptions -fno-rtti "
    @EXTRA_CFLAGS += " "
		@NAME = "ustl"
    #@IGNORED_FILES += ["ustdxept.cc","unew.cc","uexception.cc","fstream.cc"]
<<<<<<< HEAD
    @IGNORED_FILES += ["ustdxept.cc","unew.cc","uexception.cc"]
=======
    @IGNORED_FILES += ["MAMain.cpp","ustdxept.cc","unew.cc","uexception.cc"]
>>>>>>> 360d69da9f91f81d11a95cbad11e610634db77bf
	end
end

mod.invoke
