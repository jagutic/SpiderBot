# Informe Técnico

## Índice
- [1. Introducción](#1-introducción)
- [2. Diseño conceptual](#2-diseño-conceptual)
- [3. Diseño mecánico y electrónico](#3-diseño-mecánico-y-electrónico)
- [4. Fabricación](#4-fabricación)
- [5. Programación](#5-programación)
- [6. Pruebas y validación](#6-pruebas-y-validación)
- [7. Resultados](#7-resultados)
- [Referencias](#referencias)

## 1. Introducción
- 1.1 Contexto y Preparación:

    Se nos pide hacer un robot capaz de moverse en un espacio reducido. Este debe transoportar una carga (250g) mientras esquiva obstáculos y llega a su objetivo lo antes podible. El robot debe tener obligatoriamente patas (8 en nuestro caso).

    Nos hemos inspirado en inspirado en el diseño original de **MERT KILIC** [Build a Walking Robot Theo Jansen Style](https://www.pcbway.com/project/shareproject/Build_a_Walking_Robot_Theo_Jansen_Style_3D_Printed_Octopod_41bd8bdb.html). Lo hemos adaptado para que resuelva el problema propuesto. En el apartado [4. Fabricación](#4-fabricación) exponemos en detalle estos cambios.
  

- 1.2 Descripción General del Proyecto:

    Una "araña" robótica con locomoción a través del mecanismo Jansen, diseñada para el transporte de cargas ligeras en un entorno con obstáculos y paredes.
    Estructura impresa en 3D, previamente modelada en freeCAD. Programado en aruino y con posibilidad de movimiento por control remoto.

    Kit arduino UNO, 2 motores de corriente continua, 3 sensores ultrasónicos, 1 microservo 9g, 1 miniprotoboard, 1 puente H, 1 control - receptor IR.


## 2. Diseño conceptual
  
Hemos elegido el **microcontrolador arduino UNO** por nuestra previa experiencia con él y facilidad de programación. Los 2 sensores ultrasónicos laterales sirven principalmente para el seguimiento de paredes, aunque se usan como ayuda extra al esquivar obstáculos también. El ultrasonidos central mide la distancia frontal y ayuda a diferenciar entre una pared y un obstáculo en el camino.

El **control remoto**, que envía su señal gracias al receptor IR conectado al robot, nos permite cambiar de estados entre el robot para resolver los ejercicios propuestos. También disponemos de un botón de parada en caso de necesitarlo.

Estéticamente, debido a sus 8 patos y estilo arácnido, nuestro proyecto está obviamente inspirado en el famoso superhéroe Spider-man, teniendo detalles y colores de este. Esto lo hace un robot más llamativo y amigable con el usuario.

## 3. Diseño mecánico y electrónico

### 3.1 Diseño mecánico

El **mecanismo de Theo Jansen** nos permite mover el robot con únicamente 2 motores. Este movimiento circular se transfiere desde cada motor a las 4 patas de cada lado. Podemos realizar moviemientos de traslación hacia delante y detrás y rotatoria sobre si mismo gracias al puente H, que permite programar los motores en arduino para que giren en un sentido o en otro. Aqui vemos un ejemplo de su funcionamiento.

[video theo jansen]



### 3.2 Diseño electrónico

Para el control del robot se ha diseñado un PCB personalizado que actúa como escudo (shield) para el Arduino UNO. El diseño se ha realizado íntegramente en KiCad 9.0.6.

- Esquema Lógico: Se ha implementado un sistema que interconecta el microcontrolador con un driver de motores TB6612FNG, permitiendo el control independiente de los dos motores DC que accionan el mecanismo de Jansen.

- Gestión de Sensores: El diseño incluye puertos dedicados para tres sensores de ultrasonidos (frontal, izquierdo y derecho) y un microservo para la detección de obstáculos.

- Alimentación: El circuito integra una entrada de batería (V_BATT).

### 3.3 Diseño de la Placa de Circuito Impreso (PCB)

Una vez establecida la posición de los componentes, se procedió a la creación de las pistas de cobre siguiendo las guías de conexión del esquema:

- Ruteado Manual: Se han trazado todas las conexiones eléctricas utilizando pistas de cobre. Se ha priorizado evitar cruces de señales y mantener ángulos de 45° para asegurar la integridad de la fabricación.

- Verificación DRC: Se ha pasado el control de reglas de diseño (Design Rules Check) de KiCad, confirmando que no existen cortocircuitos ni pistas demasiado cercanas que impidan la fabricación.

<p align="center">
<img src="Imagenes/esquema_pcb.png" width="600">
</p>

## 4. Fabricación

En la carpeta [FreeCad_stls](FreeCad_Stls) tenemos los modelos 3D de todas las piezas. Respecto al original, hemos adaptado a nuestro problema las piezas centrales.

- Primero necesitabamos agrandar el cuerpo del robot para que los elementos necesarios quepan en él. Por lo tanto ensanchamos [PlantaBaja](FreeCad_Stls/Abajo.stl) y [PlantaMedia](FreeCad_Stls/Medio.stl).
- Hemos modificado [LateralDer](FreeCad_Stls/Der.stl) y [LateralIzq](FreeCad_Stls/Izq.stl) para que soporten una altura más, [PlantaArriba](FreeCad_Stls/Arriba.stl), de la misma forma que soportan las otras dos alturas.
- Esta planta superior sirve para dos cosas fundamentales: soportar la caja [Caja](FreeCad_Stls/Caja.stl) que llevará la carga pedida, y llevar el servo que irá enganchado a la caja contenedora del sensor de ultrasonidos [CajaUS](FreeCad_Stls/CajaUS.stl).

En las imagenes posteriores mostramos en FreeCad nuestras piezas centrales (cuerpo) ancladas.

<p align="center">
<img src="Imagenes/atras.png" width="300">
<img src="Imagenes/delante.png" width="300">
</p>

Una vez modeladas todas las piezas y mediante una impresora 3D, fabricamos todas las piezas necesarias. Estas se unen mediante difefrentes tornillos especificados abajo. Además incluimos un video tutorial para el montaje de las patas que irán conetadas a los motores sobresalientes del cuerpo.

tornillos para las plantas
tornillos para las patas
tornillo para la caja
tornillos para el servo
[video montaje patas]

### 4.1 Planteamiento y Preparación para la Fabricación del PCB

Aunque la validación final del prototipo se realizó mediante métodos de cableado físico y prototipado rápido, se ha completado toda la fase de ingeniería necesaria para su producción industrial:

- Generación de Archivos Gerber: Se ha procesado el diseño para obtener los archivos industriales estándar (formato RS-274X). Estos archivos contienen la información de las capas de cobre, máscara de soldadura y serigrafía necesaria para cualquier servicio de fabricación de PCB. [Ver carpeta](SpiderBot_KICAD/gerbers_spider)

- Escalabilidad: El diseño queda listo para una fase de producción en masa, lo que permitiría eliminar el cableado manual actual, reduciendo el peso total del robot y aumentando la fiabilidad ante las vibraciones del mecanismo Jansen.

- Validación de Montaje (3D): Se ha utilizado el motor de renderizado 3D de KiCad para verificar que la disposición de los componentes físicos (como el driver TB6612FNG y los sensores) no presenta interferencias mecánicas con el chasis del robot.

<p align="center">
<img src="Imagenes/pcb_3d.png" width="600">
</p>

## 5. Programación

Hemos dividido el código arduino en 3 ficheros:
- [Control.h](Spider/Control.h): Constantes y librerías necesarias para la implementación del control remoto. De esta forma, basta con importar este archivo para poder ejecutar diferentes acciones dependiendo del botón pulsado.
- [Spider.h](Spider/Spider.h): Clase que implementa las funcionalidades básicas del robot (move, turn, head_set_to, set_speed, get_dist). De esta forma tenemos el control del robot modulado y sus constantes (pines, umbrales) separadas del código principal).
- [Spider.ino](Spider/Spider.ino): Código principal del robot. Usa los archivos anteriores para completar el problema propuesto. Problemas específicos como seguir la pared o comprobar si hay un obstáculo, se modulan mediante métodos (follow_wall, is_obstacle). Usando estas funciones y mediante una máquina de estados, somos capaces de resolver el ejercicio propuesto. Somos capaces de cambiar entre ejercicios usando el control remoto previamente mencionado (cambia la variable de estado). Hemos evitado en la medida de lo posible utilizar delays, con el fin de hacer el programa lo más reactivo posible.

- Métodos del código principal:
  - **follow_wall**: Utilizamos un PD para seguir la pared, usando la distancia recogida por el ultrasonidos lateral correspondiente como error comprandolo con una distancia arbitraria.
  - **confirm_obstacle**: Sigue el básico concepto de, si abajo veo algo pero arriba no, es un obstáculo. Esto se debe a que lo obstáculos nunca serán más altos que 10cm, por lo que con dos simples vistazos del ultrasonidos (movido verticalmente por el servo) podemos diferenciar una pared de un objeto obstáculo.
  - **avoid_obstacle**: 

## 6. Pruebas y validación
Simulación usu
[video]
[video]

## 7. Resultados
[videos supongo]

## Referencias
Kilic, M. (2024). Build a Walking Robot Theo Jansen Style 3D Printed Octopod [Proyecto de Hardware Open Source]. PCBWay Community. https://www.pcbway.com/project/shareproject/Build_a_Walking_Robot_Theo_Jansen_Style_3D_Printed_Octopod_41bd8bdb.html
