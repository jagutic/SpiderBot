# Manual de usuario

## Índice
- [1. Introducción](#1-introducción)
- [2. Primeros Pasos](#2-primeros-pasos)
- [3. Modos de Funcionamiento](#3-modos-de-funcionamiento)
- [4. Preguntas Frecuentes](#4-preguntas-frecuentes)

## 1. Introducción

El Spider-Bot es un octópodo diseñado bajo los principios cinemáticos de Theo Jansen. Utiliza un sistema de piernas mecánicas articuladas que convierten un movimiento rotativo en un ciclo de marcha fluido y eficiente.

- Peso máximo de carga: 250g.

- Alimentación: Batería Li-Po/Li-ion de 7.4V.

- Control: Sistema autónomo con triple sensor ultrasónico y control remoto IR.

## 2. Primeros Pasos

1. Colocación: Sitúa el robot en una superficie lisa. Evita alfombras que puedan atascarse en las articulaciones de las patas.

2. Encendido: Conecta el terminal de la batería al conector de la placa.

3. Carga: Si vas a transportar el peso de 250g, asegúrate de colocarlo en el centro de la caja colocada en el superior del chasis para no forzar los motores de un solo lado.

4. Vinculación: Usa el mando para iniciar alguno de los modos de funcionamiento.

## 3. Modos de Funcionamiento

El SpiderBot se opera mediante un control remoto por infrarrojos (IR). La interfaz está dividida en funciones de Control Directo y Protocolos Autónomos.


<p align="center">
<img src="Imagenes/IR_Remote_Control" width="600">
</p>

## 4. Preguntas Frecuentes

- ¿Por qué el robot se mueve pero no avanza (se queda en el sitio)?
    - Respuesta: Comprueba que el suelo no sea demasiado resbaladizo (como cristal o parqué muy pulido). Las patas del Octopod necesitan un poco de agarre para que el mecanismo de Jansen empuje el cuerpo hacia adelante.

- ¿El robot cojea o camina torcido?
    - Respuesta: Revisa que los tornillos de las articulaciones de las patas no estén demasiado apretados. Deben moverse libremente.
 
- ¿Pierde fuerza al caminar?
    - Respuesta: La batería está baja. El driver TB6612FNG necesita buen voltaje para mover el peso del mecanismo de 8 patas.

- Le he dado al mando y no hace nada, ¿está roto?
    - Respuesta: Mira si estás apuntando directamente al "ojo" (el receptor negro) que hay sobre la superficie frontal de la caja. Además, asegúrate de que no haya una luz muy fuerte o sol directo dándole al robot, ya que eso "ciega" el control remoto.

- ¿Qué pasa si una pata se suelta o se cae?
    - Respuesta: No fuerces el motor. El robot está impreso en 3D y las piezas van unidas por ejes. Si una pata se sale, apaga el robot inmediatamente y vuelve a encajarla con cuidado.

- ¿Cómo sé si se le ha acabado la pila?
    - Respuesta: Notarás que el robot camina muy despacio, que los sensores fallan o que se reinicia solo. Es hora de cargar la batería.

`Si ves que sale humo o huele a quemado, desconecta el cable de la batería inmediatamente!!!`




























