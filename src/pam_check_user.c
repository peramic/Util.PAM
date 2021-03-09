/*
  apt-get install libpam0g-dev
 */

#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <stdio.h>

static struct pam_conv conv = {
	misc_conv,
	NULL
};

int main(int argc, char *argv[])
{
	if(argc != 2) {
		exit(2);
	}

	// redirect stdout and stderr
	freopen("/dev/null", "w", stdout);
	freopen("/dev/null", "w", stderr);

	pam_handle_t *pamh=NULL;
	int retval;
	const char *user=argv[1];

	retval = pam_start("pam-check-user", user, &conv, &pamh);

	if (retval == PAM_SUCCESS)
		retval = pam_authenticate(pamh, PAM_SILENT);

	// check if the user is disabled
	//if (retval == PAM_SUCCESS)
	//	retval = pam_acct_mgmt(pamh, 0);

	if (pam_end(pamh,retval) != PAM_SUCCESS) {
		pamh = NULL;
		fprintf(stderr, "pam-check-user: failed to release authenticator\n");
		exit(1);
	}

	// close redirected stdout and stderr
	fclose(stdout);
	fclose(stderr);

	return (retval == PAM_SUCCESS ? 0 : 1);
}