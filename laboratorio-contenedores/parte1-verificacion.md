# Parte 1: verificación de la instalación de Docker
 
## Datos generales
 
- **Versión de Docker:** 29.8.0-1 (cliente y servidor).
- **Sistema operativo:** Ubuntu 24.04.5 LTS (Linux).
- **Recursos del entorno:** 2 CPUs y unos 7,7 GiB de memoria.

 
## Paso: docker --version
 
**Qué se hizo:** Se Consulto la versión de Docker instalada en el entorno.
 
**Comando ejecutado:**
 
```bash
docker --version
```
 
**Explicación (para qué sirve el comando):** Muestra la versión del cliente de Docker y confirma que el comando `docker` existe y se puede ejecutar. Por sí solo no comprueba que el servicio de Docker esté funcionando.
 
**Resultado obtenido:**
 
```text
Docker version 29.8.0-1, build 88096ef00576baf72a9cb45caa45c0544c40e0a7
```
 
**Reflexión:** Este comando es la prueba más básica: me dice que Docker está instalado y qué versión tengo, algo útil para reportar errores o comparar con la documentación. Aun así, no me asegura que todo esté funcionando, por eso hice también `docker info`.
 
## Paso: docker info
 
**Qué se hizo:** Se pidio la información general del cliente y del servidor de Docker. Pego solo la sección `Server`, porque la del cliente solo lista plugins.
 
**Comando ejecutado:**
 
```bash
docker info
```
 
**Explicación (para qué sirve el comando):** Muestra el estado del servicio de Docker y de la máquina donde corre: cuántos contenedores e imágenes hay, versión del servidor, drivers de almacenamiento y de logs, runtimes, redes disponibles, opciones de seguridad, kernel, sistema operativo y recursos. Si el servidor no está activo, el comando falla al conectarse y no muestra la sección `Server`.
 
**Resultado obtenido (parcial, sección Server):**
 
```text
Server:
 Containers: 1
  Running: 0
  Paused: 0
  Stopped: 1
 Images: 1
 Server Version: 29.8.0-1
 Storage Driver: overlayfs
  driver-type: io.containerd.snapshotter.v1
 Logging Driver: json-file
 Cgroup Driver: cgroupfs
 Cgroup Version: 2
 Plugins:
  Volume: local
  Network: bridge host ipvlan macvlan null overlay
  Log: awslogs fluentd gcplogs gelf journald json-file local splunk syslog
 CDI spec directories:
  /etc/cdi
  /var/run/cdi
 Swarm: inactive
 Runtimes: io.containerd.runc.v2 runc
 Default Runtime: runc
 Init Binary: docker-init
 containerd version: db8809540e1a7a9da5d518876894933ff55692ab
 runc version: 8f2685a471d3347a686ad3909783d8aafc6bb208
 init version: 
 Security Options:
  apparmor
   Profile: default
  seccomp
   Profile: builtin
  cgroupns
 Kernel Version: 6.8.0-1064-azure
 Operating System: Ubuntu 24.04.5 LTS (containerized)
 OSType: linux
 Architecture: x86_64
 CPUs: 2
 Total Memory: 7.756GiB
 Name: codespaces-bd0be3
 ID: 71779934-80e3-4fdc-be4e-c1600e3d30ce
 Docker Root Dir: /var/lib/docker
 Debug Mode: false
 Username: codespacesdev
 Experimental: false
 Insecure Registries:
  ::1/128
  127.0.0.0/8
 Live Restore Enabled: false
 Firewall Backend: iptables
  EnableUserlandProxy: true
  UserlandProxyPath: /usr/libexec/docker/docker-proxy
```

## Qué información muestra docker info
 
`docker info` reúne en un solo lsugar el estado de Docker. Del lado del cliente muestra la versión y los plugins instalados. Del lado del servidor muestra cuántos contenedores (en ejecución, pausados y detenidos) e imágenes existen, la versión del motor, cómo guarda los datos (`overlayfs`) y los logs (`json-file`), qué runtimes y redes hay disponibles, las opciones de seguridad activas (AppArmor y seccomp) y datos de la máquina: kernel, sistema operativo, arquitectura, CPUs y memoria.
 
## Por qué es importante verificar la instalación antes de continuar
 
Todas las partes siguientes dependen de que Docker responda correctamente. Si no verifico desde el inicio y algo falla, un error posterior podría parecer un problema del comando o del Dockerfile cuando en realidad es del entorno (por ejemplo, que el servicio no esté activo). Comprobarlo primero me ahorra tiempo y confusión.
 
## Preguntas de reflexión
 
1. **¿Qué diferencia hay entre instalar Docker y tener Docker ejecutándose correctamente?**
   Instalar Docker significa que el programa y el comando `docker` existen en el sistema. Tenerlo funcionando significa además que el servicio en segundo plano está activo y que el cliente puede conectarse a él. Por eso `docker --version` solo prueba lo primero, mientras que `docker info` con la sección `Server` prueba lo segundo.
2. **¿Qué información útil muestra el comando docker info?**
   Muestra cuántos contenedores e imágenes hay, la versión del servidor, el driver de almacenamiento, los runtimes y las redes disponibles, la configuración de seguridad y datos del equipo como el kernel, el sistema operativo, las CPUs y la memoria. Me sirve para confirmar que Docker funciona y para entender en qué entorno corren mis contenedores.
3. **¿Por qué Docker necesita un servicio o daemon ejecutándose en segundo plano?**
   Porque el comando `docker` es solo un cliente que envía órdenes. El trabajo real (descargar imágenes, crear y mantener los contenedores, administrar redes y volúmenes) lo hace el daemon. Al correr en segundo plano, los contenedores siguen funcionando aunque cierre la terminal desde la que los lancé.
