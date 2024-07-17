# SDRstick UDP-HF1

Este SDR no tiene soporte oficial para GNR Radio 3.10. Para usarlo hay que crear un pipe (por ejemplo, sdrstick.dat) antes.

Luego preparar el SDR, preferentemente con IP fija (por ejemplo, 192.168.2.2). Testear con ping que haya conexión.

Para usar el SDR con GNU Radio 3.10 hay que seguir los siguentes pasos:

1. Lanzar el .grc que usar un bloque file source al pipe
Por ejemplo ```python3 -u SDRstick.py```

2. Lanzar el código ```./sdrstick-udpserv``` ubicado en carpeta sdrstick-soft

3. Configurar el SDR para el espectro a trabajar:

```
cd <path to sdrstick-soft folder>
./sdrstick-magic
./sdrstick-set-frec 192.168.2.2 1175000
./sdrstick-set-1.25M 192.168.2.2
./sdrstick-run 192.168.2.2
```

Comando alternativos
```
./sdrstick-stop 192.168.2.2
./sdrstick-set-384k 192.168.2.2
```



