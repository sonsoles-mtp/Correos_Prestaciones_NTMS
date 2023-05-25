vuser_init()
{
	web_set_sockets_option("SSL_VERSION", "2&3");
	web_set_max_html_param_len("50000");
	
	web_add_header("Content-Type","application/x-www-form-urlencoded");
	
	web_reg_save_param_ex(
		"ParamName=token",
		"LB=id_token\":\"",
		"RB=\"",
		SEARCH_FILTERS,
		LAST);
	
	lr_start_transaction("SCR01_TR01_EMBARRIADO_NOTIFICACIONES_TOKEN");
	
	web_submit_data("token",
		"Action=https://pocisam.correospre.es/mga/sps/oauth/oauth20/token",
		"Method=POST",
		"Mode=HTTP",
		ITEMDATA,
		"Name=grant_type", "Value=client_credentials", ENDITEM,
		"Name=client_id", "Value=hades", ENDITEM,
		"Name=client_secret", "Value=PbCc1xzVLyg1878ti0US", ENDITEM,
		"Name=scope", "Value=openid", ENDITEM,
		LAST);
	
	lr_end_transaction("SCR01_TR01_EMBARRIADO_NOTIFICACIONES_TOKEN",LR_AUTO);
	
	
	return 0;
}
