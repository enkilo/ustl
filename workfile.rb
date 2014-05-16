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
    @EXTRA_CFLAGS += " -DHAVE_STDINT_H=1 -fno-exceptions -fno-rtti "
		@NAME = "ustl"
    @IGNORED_FILES += [""]
	end
end

mod.invoke
