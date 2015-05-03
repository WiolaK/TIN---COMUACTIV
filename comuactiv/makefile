#COMUACTIV makefile
#Author: Jan Kumor

#separator
SEP="****************************"

#modules
MODULES=proto ce_app fe_app
CMODULES=$(addsuffix .clean, $(MODULES))

.PHONY: all $(MODULES)

all: $(MODULES)

$(MODULES):
	@echo $(SEP)
	@echo " Building COMUACTIV::"$@
	@echo $(SEP)
	$(MAKE) -C $@

ce_app: proto

fe_app: proto

.PHONY: clean $(CMODULES)

clean: $(CMODULES)

$(CMODULES): %.clean:
	@echo $(SEP)
	@echo " Cleaning COMUACTIV::"$*
	@echo $(SEP)
	$(MAKE) clean -C $*
		
	

