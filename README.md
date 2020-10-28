# pam_close_systemd_system_dbus
Workaround for XRDP #1684

THIS IS A HACK - DO NOT USE IT IN PRODUCTION. IT HAS ONLY BEEN TESTED IN
A NARROW RANGE OF CIRCUMSTANCES.

This is a minimal PAM module which can be inserted into the Arch/Manjaro
/etc/pam.d/xrdp-sesman file as follows:-

<pre>
#%PAM-1.0
auth        include     system-remote-login
account     include     system-remote-login
password    include     system-remote-login
<b>session     optional	pam_close_systemd_system_dbus.so</b>
session     include     system-remote-login
</pre>

For systemd 246, this has the effect of breaking the connection made to
the system DBUS by pam_systemd_home.so during authentication. As a result, the
pam_systemd.so module running in a different PID creates a new connection,
and a systemd session is created successfully.

Other workarounds are:-
- removing pam_systemd_home.so from /etc/pam.d/system-auth.

The correct solution is to update xrdp-sesman to call pam auth and session
stages from the same PID.
