# vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
# Makefile template

THISPROJECT="json-utils"
THISDATE=`date`

JSON_C_DIR=/usr
CFLAGS += -I$(JSON_C_DIR)/include/json-c
LDFLAGS+= -L$(JSON_C_DIR)/lib -ljson-c

all: init jsonread jsonwrite
#	@make git-getdescription
#	@make git-setdescription
	@echo "\n* Compiled all targets for $(THISPROJECT) project."
	@exit 0

jsontest: init jsontest.c
	@gcc -O3 jsontest.c utils.c -ljson-c -std=c99 -o jsontest
	@echo "* Build finished: 'jsontest'"
	@exit 0

jsonread: init jsonread.c
	@gcc -O3 jsonread.c utils.c  -ljson-c -std=c99 -o jsonread
	@echo "* Build finished: 'jsonread'"
	@exit 0

jsonwrite: init jsonwrite.c
	@gcc -O3 jsonwrite.c utils.c -ljson-c -std=c99 -o jsonwrite
	@echo "* Build finished: 'jsonwrite'"
	@exit 0
strip: 
	@if [ -f jsonread ]; then  strip "jsonread"; echo "* Stripped jsonread"; fi
	@if [ -f jsonwrite ]; then  strip "jsonwrite"; echo "* Stripped jsonwrite"; fi
	@echo "\n* Stripped all built files."
	@exit 0

install: 
	@if [ -f jsonread ]; then  cp jsonread ~/scripts/jsonread; echo "* Installed jsonread"; fi
	@if [ -f jsonwrite ]; then  cp jsonwrite ~/scripts/jsonwrite; echo "* Installed jsonwrite"; fi
	@echo "\n* Installed all built files."
	@exit 0
##	
##iniread: init src/ini-read.c
##	@gcc -O3 -o build/$(INIREAD) src/$(INIREAD).c src/utils.c src/minIni.c
##	@strip build/$(INIREAD)
##	@echo "* Build finished: '$(INIREAD)'"
##	@exit 0

##iniwrite: init src/ini-write.c
##	@gcc -O3 -o build/$(INIWRITE) src/utils.c src/minIni.c src/$(INIWRITE).c
##	@strip build/$(INIWRITE)
##	@echo "* Build finished: '$(INIWRITE)'"
##	@exit 0

init:
##	@echo "//automatically generated by make" > src/build-date.h
##	@echo " " >> src/build-date.h
##	@echo "#define BUILD_DATE \"$(THISDATE)\"" >> src/build-date.h
	@exit 0


clean: 
##	@if [ -f build/$(INIREAD) ]; then  rm "build/$(INIREAD)"; echo "* Removed $(INIREAD)"; fi
##	@if [ -f build/$(INIWRITE) ]; then  rm "build/$(INIWRITE)"; echo "* Removed $(INIWRITE)"; fi
###	@if [ -f build/git-getdescription ]; then rm build/git-getdescription; echo "removed git-getdescription"; fi
	@echo "\n* Cleaned all built files."
	@exit 0

#.PHONY: test help


