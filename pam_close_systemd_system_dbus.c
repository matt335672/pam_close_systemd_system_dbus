/*
 * Close DBUS system bus connection
 */

#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <sys/syslog.h>

static void pam_close_systemd_system_dbus(pam_handle_t *pamh)
{
    const void *conn;
    const char *var = "systemd-system-bus";
    int status;

    if (pam_get_data(pamh, var, &conn) == PAM_SUCCESS)
    {
        if ((status =pam_set_data(pamh, var, 0, 0)) == PAM_SUCCESS)
        {
            pam_syslog (pamh, LOG_NOTICE, "\"%s\" was cleared", var);
        }
        else
        {
            pam_syslog (pamh, LOG_NOTICE, "\"%s\" could not be cleared [%d]", var, status);
        }
    }
    else
    {
        pam_syslog (pamh, LOG_NOTICE, "\"%s\" was not defined", var);
    }
}

int
pam_sm_open_session(pam_handle_t *pamh, int flags,
		    int argc, const char **argv)
{
    pam_close_systemd_system_dbus(pamh);
    return PAM_SUCCESS;
}

int
pam_sm_close_session(pam_handle_t *pamh, int flags,
		     int argc, const char **argv)
{
    return PAM_SUCCESS;
}
