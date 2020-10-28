MOD = pam_close_systemd_system_dbus

APP = $(MOD).so
SRC = $(MOD).c
OBJ = $(MOD).o

DEBUG = -g

DEST = /usr/lib/security

INSTALL = /usr/bin/install

$(APP) : $(OBJ)
	$(CC) -shared $(DEBUG) -o $@ $< -lpam

$(OBJ) : $(SRC)
	$(CC) -fPIC -c $(DEBUG) $<

install: $(APP)
	$(INSTALL) $(APP) $(DEST)

clean:
	$(RM) $(APP) $(OBJ)
