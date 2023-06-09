SCR01_TR00_EMBARRIADO_NOTIFICACIONES()
{
	web_set_sockets_option("SSL_VERSION", "2&3");
	web_set_max_html_param_len("50000");
	
	web_add_header("Content-Type","application/x-www-form-urlencoded");
	lr_think_time(3);
	
	web_reg_find("Text=Asignado correctamente.", LAST);
	
	//web_reg_find("Text=Realizada asignaci\xC3\xB3n mediante el sistema Aguas Abajo.", LAST);
	//createdOn
	//OJO AHORA Realizada asignaci\xC3\xB3n mediante Notificaciones.c(11):     el sistema Aguas Abajo.
	
	lr_start_transaction("SCR01_TR02_EMBARRIADO_NOTIFICACIONES_ASSIGMENT");
	
	web_rest("POST: https://api1-intapp.correospre.es/logistics/logist...",
		"URL=https://api1-intapp.correospre.es/logistics/logistics/api/v1/assignment",
		"Method=POST",
		"EncType=raw",
		"Body={\r\n"
		"\"adminMode\": true,\r\n"
		//"\"assignmentDate\": \"${__time(YYYY-MM-dd,fecha_actual)}T${__time(HH:MM:ss,hora_actual)}+0100\",\r\n"
		"\"assignmentDate\": \"{fec_actual}\",\r\n"
		"\"deliveryManCode\": \"P001234\",\r\n"
		"\"device\": \"2738632764\",\r\n"
		"\"interfaceId\": \"AI00001\",\r\n"
		"\"itemId\": \"{cod_bulto_notificacion}\",\r\n"
		//"\"language\": \"Espa�ol\",\r\n"
		"\"language\": \"Espa&#241;ol\",\r\n"
		"\"latitude\": 23.5,\r\n"
		"\"longitude\": 12.4,\r\n"
		"\"route\": \"{id_ruta_notificacion}\",\r\n"
		"\"centerCode\": \"{cod_centro_notificacion}\",\r\n"
		"\"onRoute\": false,\r\n"
		"\"userCode\": \"E012345\",\r\n"
		"\"changeProduct\": 0\r\n"
		"}\r\n",
		HEADERS,
		"Name=Authorization", "Value=Bearer {token}", ENDHEADER,
		"Name=Content-Type", "Value=application/json", ENDHEADER,
		LAST);

	lr_end_transaction("SCR01_TR02_EMBARRIADO_NOTIFICACIONES_ASSIGMENT",LR_AUTO);
	
	lr_think_time(3);
	
	//createdOn
	web_reg_find("Text=createdOn", LAST);
	
	lr_start_transaction("SCR01_TR03_EMBARRIADO_NOTIFICACIONES_OUTPUTDELIVERY");
	
	web_rest("POST: https://api1-intapp.correospre.es/logistics/logist...",
		"URL=https://api1-intapp.correospre.es/logistics/logistics/api/v1/outputdelivery",
		"Method=POST",
		"EncType=raw",
		"Body={\r\n"
		"\"centerId\": \"{cod_centro_notificacion}\",\r\n"
		//"\"deliveryServiceDate\": \"${__time(YYYY-MM-dd,fecha_actual)}T${__time(HH:MM:ss,hora_actual)}+0100\",\r\n"
		"\"deliveryServiceDate\": \"{fec_actual}\",\r\n"
		"\"deviceCode\": \"2738632764\",\r\n"
		"\"interfaceCode\": \"INT1047859\",\r\n"
		//"\"modifiedDate\": \"${fecha_actual}T${hora_actual}+0100\",\r\n"
		"\"modifiedDate\": \"{fec_actual}\",\r\n"
		"\"route\": \"{id_ruta_notificacion}\",\r\n"
		"\"userCode\": \"P001234\"\r\n"
		"}\r\n",
		HEADERS,
		"Name=Authorization", "Value=Bearer {token}", ENDHEADER,
		"Name=Content-Type", "Value=application/json", ENDHEADER,
		LAST);

	lr_end_transaction("SCR01_TR03_EMBARRIADO_NOTIFICACIONES_OUTPUTDELIVERY",LR_AUTO);
	
	return 0;
}
