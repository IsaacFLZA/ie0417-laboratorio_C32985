# Parte 7: publicación de puertos

<!-- Documentacion requerida (borrar este comentario al terminar):
- [ ] Qué significa -p 5000:5000
- [ ] Qué significa -p 8080:5000
- [ ] Cuál puerto pertenece al host
- [ ] Cuál puerto pertenece al contenedor
- [ ] Captura del navegador mostrando la aplicación funcionando
-->

## Paso: Publicar el puerto 5000:5000

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker run --name app-puertos -p 5000:5000 laboratorio-flask:1.0
# abrir http://localhost:5000 y http://localhost:5000/info
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Detener y eliminar

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker stop app-puertos
docker rm app-puertos
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Otro puerto del host: 8080:5000

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker run --name app-puertos-2 -p 8080:5000 laboratorio-flask:1.0
# abrir http://localhost:8080
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Detener y eliminar

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker stop app-puertos-2
docker rm app-puertos-2
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Significado de -p 5000:5000 y -p 8080:5000


## Preguntas de reflexión

1. **¿Por qué no basta con que la aplicación escuche en el puerto 5000 dentro del contenedor?**

   Respuesta: 

2. **¿Qué función cumple el mapeo de puertos?**

   Respuesta: 

3. **¿Cuál es la diferencia entre el puerto del host y el puerto del contenedor?**

   Respuesta: 

4. **¿Qué pasaría si dos contenedores intentan usar el mismo puerto del host?**

   Respuesta: 


---

## Logs e inspección

<!-- Parte 8. Documentar: qué muestra docker logs; para qué sirve docker logs -f; qué tipo de información muestra docker inspect; qué información muestra docker stats. -->

## Paso: Ejecutar en segundo plano y ver logs

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker run -d --name app-logs -p 5000:5000 laboratorio-flask:1.0
docker logs app-logs
docker logs -f app-logs
# en otra terminal o navegador: http://localhost:5000 y /info
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Inspeccionar y revisar recursos

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker inspect app-logs
docker stats
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Detener y eliminar

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker stop app-logs
docker rm app-logs
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

### Preguntas de reflexión (logs)

1. **¿Por qué los logs son importantes al trabajar con contenedores?**

   Respuesta: 

2. **¿Qué diferencia hay entre ver logs históricos y logs en tiempo real?**

   Respuesta: 

3. **¿Qué información útil se puede obtener con docker inspect?**

   Respuesta: 

4. **¿Por qué es importante observar el consumo de recursos?**

   Respuesta: 


---

## Variables de entorno

<!-- Parte 9. Documentar: qué hace la opción -e; qué cambió en la aplicación; por qué no fue necesario reconstruir la imagen; capturas o salidas de ambas ejecuciones. -->

## Paso: Primera ejecución con MENSAJE

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker run --name app-env -p 5000:5000 -e MENSAJE="Hola desde una variable de entorno" laboratorio-flask:1.0
# abrir http://localhost:5000
docker stop app-env
docker rm app-env
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Segunda ejecución con otro MENSAJE

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker run --name app-env-2 -p 5000:5000 -e MENSAJE="Configuración cambiada sin modificar la imagen" laboratorio-flask:1.0
# abrir http://localhost:5000
docker stop app-env-2
docker rm app-env-2
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

### Preguntas de reflexión (variables de entorno)

1. **¿Por qué es útil configurar aplicaciones mediante variables de entorno?**

   Respuesta: 

2. **¿Qué tipo de información podría configurarse así?**

   Respuesta: 

3. **¿Por qué no es buena práctica guardar contraseñas directamente dentro del código?**

   Respuesta: 

4. **¿Qué ventaja tiene usar la misma imagen con diferentes configuraciones?**

   Respuesta: 

