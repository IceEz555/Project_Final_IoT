#ifndef TASK_MQTT_AWS
#define TASK_MQTT_AWS

#if AWS_ENABLED == true
    #include <Arduino.h>
    #include <WiFiClientSecure.h>
    #include <MQTTClient.h>
    #include "../config/config.h"

    extern unsigned short measurements[];

    #define AWS_MAX_MSG_SIZE_BYTES 300

    WiFiClientSecure AWS_net;
    MQTTClient AWS_mqtt = MQTTClient(AWS_MAX_MSG_SIZE_BYTES);

    const char AWS_CERT_CA[] = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

    const char AWS_CERT_PRIVATE[] = R"EOF(-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEApSmUsvfN9J0TT0ZoWtKe58iCSUoGUgD9jQKdW+j3adn5rd1d
XaXmkElwFPY0FuFFJtTTJMjf7cC6U1NkFbpsvHXBLjxFthayifUo+X9+Y3wF4fC4
JleF0fJB9Zm3gvSj+ZNZ5+hdGV/ce/hyHBpcTtseKuEcQhRyx6u6TnLFrKzBJCB9
s4JqVnpG/Su7+F8HlMw1dq3jHVTcR+QIFlZ7Np++rHgqJbiHS7rC3dHhezEHAp70
gd+FWx4nliGzfBKi2st61R2nRb3BzTT1vJQRv4ntlbwN71hQJxAypdQ5y5zPdANv
Y1FbEPJUcXjHO94trZVH6WbQFEmOYSwvBp8XAwIDAQABAoIBAFnM1uXL6HZUpTgY
Lwsas32Qvo38qp0Rnsp5nndnnoY2FxQaZPZTCp5u33r2NnIuP3wSgU7hzScm/+fo
UmWh/Bcn60YpTTno82AhJQsq79xFhalIScfHFKKHFqfj0SxpuXIsVNjLtTrjrSzW
c6ymBIR3jNqBlOy004eO7nhS3Pm6ACLSWYlj4DL3Zlo+A09t3W15qEKHgOgd4Yj+
uw19ulc3H+wk4NLXW8OUxdaSkSg/ELhT9IUWjPfut1gJ+nwoi5XkyPpfyXVFi8GY
Sxpe5MJEvJ1YZ/K8BwgIC7RA++Sv8dKv7/Zw3Ot8bLwBVxKraMP0LIxkCyWvq0mw
c9sOX4ECgYEA22WvqNOXkx+DrZXTLLdKv2aySsES+kb9WKy83ixsZEYo46u8wXro
mtS7MR6yfGJ/8nJ8PotzTbC4riYUxFSck6Pk3+Bp8XmvJt0AfB0zNI2lj3o8RQOz
12tr2Ep4iHJ3uvciqc8YjvEHlkumA2ZpmDZdJ0jtIq1+2CkHn9bXM8ECgYEAwLeP
1FZ0yH6+uWfGPTaCgVue5Naj9Wt4DfS9bJGMaCioLND6pybMZiWJzOhACQ1IB+4b
9z1CimWqfDobrDdwXws3n8hY9WgsSJjxiJGFEKe9mDE7TwXHgRLWgkGw04bLnefR
nYYFCBGChmTjEqkS/uS5O9vSK5qSHu+TVo5Ra8MCgYEAzrFX8ieVjyeLeIfEMUZl
BzkLE14eMOecWmQycuVLIJTwhL0Q0P6oEOYFjNssr/5kJ9cvsgTSlgi9lGOQAP7t
nDI1t6zGYpaPKn/eqw8fZI1lwmwYR7SbQ4GSUmymbXXZ0qxtXakbq97rlO6j8mQT
azEcRZxwu9DTxXWyFyXiDIECgYAznzf8xefkaOcH3P9iGD7fDb7DR6eFrvLqshsn
gNlecT2TO6tYqPDpj7aY18GHazJXRXXiRVuUnOUM/7e36uXD38pXl6AUpIHwNF/G
mExPiM8lfFKJuV+WeIhTPetyzdGvC5C/pE2muqH/A/k7X2TCOFxR53El0vK/LKeH
8PloZwKBgBs3KgkzhZzx/cUkwInn8vCgbOLQ9A+ofKf3N1vCPsl5sbwB7z906bLY
0I4UQ1SYCQrWqnC80U/FuJ4fmyHTloiSzhcyTpVzdSd5Nhye5ew4xktmcA6BQOYa
oDU61e8wQyInTS/l84kzthARBfTu8MScB3SibqjpA+5Clum/0BEf
-----END RSA PRIVATE KEY-----
)EOF";

    const char AWS_CERT_CRT[] = "-----BEGIN CERTIFICATE-----\n"
"MIIDWjCCAkKgAwIBAgIVAJ1o4fjb2PpGG8OXWj6dIy4xRYjKMA0GCSqGSIb3DQEB\n"
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNTAxMjUwNzE3\n"
"MzZaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQClKZSy9830nRNPRmha\n"
"0p7nyIJJSgZSAP2NAp1b6Pdp2fmt3V1dpeaQSXAU9jQW4UUm1NMkyN/twLpTU2QV\n"
"umy8dcEuPEW2FrKJ9Sj5f35jfAXh8LgmV4XR8kH1mbeC9KP5k1nn6F0ZX9x7+HIc\n"
"GlxO2x4q4RxCFHLHq7pOcsWsrMEkIH2zgmpWekb9K7v4XweUzDV2reMdVNxH5AgW\n"
"Vns2n76seColuIdLusLd0eF7MQcCnvSB34VbHieWIbN8EqLay3rVHadFvcHNNPW8\n"
"lBG/ie2VvA3vWFAnEDKl1DnLnM90A29jUVsQ8lRxeMc73i2tlUfpZtAUSY5hLC8G\n"
"nxcDAgMBAAGjYDBeMB8GA1UdIwQYMBaAFOx2IXRrZDpOcMTlH1g8ti5yQB6dMB0G\n"
"A1UdDgQWBBSkE58lJqmHz0CtKdwxNDiMBHPKcjAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAgFzUfkLLW/PqzkqfMc5XIEOP\n"
"HgpG02Co81nxyVBmqGDhl4SaOn9Cpp4hEr8/ByyAi+pcNgUlxMBXYA7DXyWYlhyd\n"
"FmxZ/9MWbTk2ZF90HNuRJqIE2JZYvOBr1Hv2KrE5YQAL/5R7Hn5kmiAlFQQ9J/rI\n"
"P+6kJ/jnethvA1mKc/UoHWKzkI1In/TcMYGifWQ3wYwjgVuvlUHDq2BE/qN/kGRD\n"
"AfzTSU+vEouZAp2pTlbdBkVBNmt0kPjnfSPI4uEjOUpsrkhiSY4kY38Zjk6x6NJ9\n"
"x+kSiQUNFBMUUAEzQ2JgutfOoByLfjld7nNN9YxGoCBNpcobUmSfcxRETLDElw==\n"
"-----END CERTIFICATE-----";


    void keepAWSConnectionAlive(void * parameter){
        for(;;){
            if(AWS_mqtt.connected()){
                AWS_mqtt.loop();
                vTaskDelay(500 / portTICK_PERIOD_MS);
                continue;
            }

            if(!WiFi.isConnected()){
                vTaskDelay(1000 / portTICK_PERIOD_MS);
                continue;
            }

            // Configure certificates
            AWS_net.setCACert(AWS_CERT_CA);
	        AWS_net.setCertificate(AWS_CERT_CRT);
	        AWS_net.setPrivateKey(AWS_CERT_PRIVATE);

            serial_println(F("[MQTT] Connecting to AWS..."));
            AWS_mqtt.begin(AWS_IOT_ENDPOINT, 8883, AWS_net);

            long startAttemptTime = millis();
        
            while (!AWS_mqtt.connect(DEVICE_NAME) &&
                    millis() - startAttemptTime < MQTT_CONNECT_TIMEOUT)
            {
                vTaskDelay(MQTT_CONNECT_DELAY);
            }

            if(!AWS_mqtt.connected()){
                serial_println(F("[MQTT] AWS connection timeout. Retry in 30s."));
                vTaskDelay(30000 / portTICK_PERIOD_MS);
            }

            serial_println(F("[MQTT] AWS Connected!"));
        }
    }

    /**
     * TASK: Upload measurements to AWS. This only works when there are enough
     * local measurements. It's called by the measurement function.
     */
    void uploadMeasurementsToAWS(void * parameter){
        if(!WiFi.isConnected() || !AWS_mqtt.connected()){
            serial_println("[MQTT] AWS: no connection. Discarding data..");
            vTaskDelete(NULL);
        }

        char msg[AWS_MAX_MSG_SIZE_BYTES];
        strcpy(msg, "{\"readings\":[");

        for (short i = 0; i < LOCAL_MEASUREMENTS-1; i++){
            strcat(msg, String(measurements[i]).c_str());
            strcat(msg, ",");
        }

        strcat(msg, String(measurements[LOCAL_MEASUREMENTS-1]).c_str());
        strcat(msg, "]}");
            
        serial_print("[MQTT] AWS publish: ");
        serial_println(msg);
        AWS_mqtt.publish(AWS_IOT_TOPIC, msg);

        // Task is done!
        vTaskDelete(NULL);
    }
#endif
#endif