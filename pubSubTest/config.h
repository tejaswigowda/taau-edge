#include <pgmspace.h>

#define THINGNAME "taau_1"

const char WIFI_SSID[] = "NETGEAR31";
const char WIFI_PASSWORD[] = "fluffywind2904";
const char AWS_IOT_ENDPOINT[] = "a160q36fslcfae-ats.iot.us-east-1.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
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

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUJLoX7xpdexl/mwCDFpNvoXk7umUwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIyMDMyODIxMDc1
OVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBANrIcLpyXGN6KZSaAKqM
kMawhxaoVt+X8+UDtL4yuZa11bqPZbUzI4N44ncNY+YUiR4gS/ihqdpeiq4Er94K
oYlxNp49p/kIuI89xnr7DH5WswnLPHT+NNArU5foWFjEeARoEQxbV3LWBAkprdQ7
ERjjsiF/BLMTJL8GpyIXcmqBal0rPzthtfj8W7l0uS/94CUEgkT0ZbXei7xUOliG
cllXfDe+pDEYWyyCv3ggg+ZD3KZ1TPBgYX0OjquxSdNBx8+Q5Ew4EBvCf65UOdoK
Zffwb0OVH0HVy/VHGlOcG1B6lQnnUHBEzQSiiA/X2AnWrv0qCU8KeAFrWpAbjOWN
o0sCAwEAAaNgMF4wHwYDVR0jBBgwFoAUh4pN6c7wjtmRsV4Otm3JTpHyM9swHQYD
VR0OBBYEFJx3t2x5nrHAlEpR+nzF5DDNzzAaMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCCDqldYyayQ5FUsgCC4vrQ33dN
fUjcNHSAMgxom6xt9TjC5bC6BLwiy6gy5Ucv5/JVyrKOtI/qLonkMYcTBAxjqPkr
BoZQFZ4UMnCFNgDdTpNXFaUUPQLliK3QxclWLKiI35DqZYR5WUj6LuB6Lfs38eY0
rc9UXyIAOz1WfNp0VE6jesvEYvdNpiMPgnz9N3hssAnu7mOmyXclJ/kpyP1LeW7P
yaT7wzLvNuQ6Z9yjWp/GqDknSioYqSCUUILFPeV+GT/5d7i+lQhf6s2HpfTofPTJ
EaFnc2TdxBIk7/jwoUiK1B8+F9tEv0LUVPx5iKKydkG3LJy5HkXc10eMsEt/
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEA2shwunJcY3oplJoAqoyQxrCHFqhW35fz5QO0vjK5lrXVuo9l
tTMjg3jidw1j5hSJHiBL+KGp2l6KrgSv3gqhiXE2nj2n+Qi4jz3GevsMflazCcs8
dP400CtTl+hYWMR4BGgRDFtXctYECSmt1DsRGOOyIX8EsxMkvwanIhdyaoFqXSs/
O2G1+PxbuXS5L/3gJQSCRPRltd6LvFQ6WIZyWVd8N76kMRhbLIK/eCCD5kPcpnVM
8GBhfQ6Oq7FJ00HHz5DkTDgQG8J/rlQ52gpl9/BvQ5UfQdXL9UcaU5wbUHqVCedQ
cETNBKKID9fYCdau/SoJTwp4AWtakBuM5Y2jSwIDAQABAoIBAQCc6SMIZZrjcas+
u9D8gMIY7mSEmIlt5ZJzztujicfXUmSOX+gnNB0lXt61WfIrAtFwvOMf1/p09ldq
BUyI6IEAjSUKCthc4KdVfI3MiB9mwRG5VXzvv53rKxfSHD64s3gMWQLZJO2sG9hb
JfxY+WACxNNt+KZLNNCm/MODzOMvhHvIgBVMSeiVg8kKMT66yPQjAuBiYKfIyI0B
4tJxyjlmVRVPLo+xTSBFNNxGxfHK/sxT+Df/EvkQ3wTr04BTSuDIDB2kr5iwn7mR
9LFasqiYvE7uxMczvRVUMvL9lZKfCNznHbMzsXBOjEdGZZr9Eymsh0ozFC84cPp8
3gn3Y3RxAoGBAPtkgZXM94khxSvOi3PW4I5ZZr/6mZItJDSOnQRowqWV/YkFuydA
mQaY4/GosAKnk2CpuPjyupAUkJOctn5eylFMS2IYevUQJ9OoXpGSjnnIrOaglMN6
8eMklsNwOqS4MwhhWpcp3zLIRjj+dQPGbrjVnGeMal4UR5/l30E5x6ATAoGBAN7K
71sZKQDldiUuyfWpKE4yCXBTRTruyYxWz2WJCnulWuZNWaFEoT4MW1Sfg83VVdTo
TZGtA1aiiNpb2qpNr85hhTZLvWzI3GpGfOLFqB54OwXRWM8m5LtCa5k9Ugx002o3
EF+0rymSA43magQxo5BDiCupoouMBzCp1GIrAYbpAoGAfCruXoE4moEVlEeWVYcC
rwy1VYl/pNWrFlKCd5UO3x6wdadhA0hCzSFjJQ9+sDD4+DucY0nwoA2oQ2CaOtyy
7WjTqwYQZU6vfTmiTCCpQrm9vMP/9nWZV+nQlYOvU4CvpCoBxrwlxD1rgecdANpY
Ae9wKy0NtJ4rqmyt0tepJAUCgYEAiNDqyHDdA1XmhdMD5z6oJ80Gito4K4a0cuBk
oJ/VtjTHa6KYpjZ1JpuEAqWq1V5rRUIbUJiE8lEB5cZ+tBLdIco1ejBs9T8sTH9Y
9hIXug5vgJUdCqmB0ZVqakKD/m5H3nROM9fLsaWfVSboeAbbwR4Xo2ibD0NArxu7
90UdvPECgYEAjlMapcd4V1nlHK7Owd9z/NlQPB56m4X7TTGtAhZkxmdqsSvEd+qh
u18GKc0Obuy1y45eHSb5dM67MBjw7xp6HKmtzYTIkEUKc+26IC/nOw0KjIuMXZzJ
/ZYQdelomWjHE17Le+vrQtdWHPLlW3Ar0Dy1DmaDGEIswi3aGi+Pusk=
-----END RSA PRIVATE KEY-----
)KEY";
