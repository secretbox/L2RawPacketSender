.PHONY: all
.DEFAULT_GOAL := all
cc:=gcc
clean:
	rm -rf tcchain iwaerolinkActive iwaerolinkBackupSync

tcchain: TurboChainTC.c
	$(cc) -o $@ $<
iwaerolinkActive: AeroLink_Active.c
	$(cc) -o $@ $<

iwaerolinkBackupSync: AeroLink_Backup_Sync.c
	
	$(cc) -o $@ $<
all: tcchain iwaerolinkActive iwaerolinkBackupSync
