#ifndef _REQUESTS_
#define _REQUESTS_

// calculeaza si returneaza o cerere GET
char *compute_get_request(char *host, char *url, char *query_params,
							char **cookies, int cookies_count, char **headers);

// calculeaza si returneaza o cerere POST
char *compute_post_request(char *host, char *url, char* content_type, char **body_data,
			int body_data_fields_count, char **cookies, int cookies_count, char **headers);

// calculeaza si returneaza o cerere DELETE
char *compute_delete_request(char *host, char *url, char **headers);
#endif
