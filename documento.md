---
title: Descripción de la práctica
subtitle: "Práctica 3 - Informática Gráfica"
author: Francisco David Charte Luque
lang: spanish
numbersections: yes
geometry: "a4paper, top=2.5cm, bottom=2.5cm, left=3cm, right=3cm"
---

# Grafo de escena

![Representación gráfica PHIGS del modelo jerárquico desarrollado](../p3_phigs.png)

# Lista de grados de libertad

## Rotación de la cabeza

\begin{center}\includegraphics[width=\textwidth]{../r2_grado1.png}\end{center}

* Clase: `CabezaR2`
* Métodos: `R2::girar_cabeza`, `CabezaR2::girar`
* Rango de valores: $[0, 1]$
* Unidades: Valores adimensionales (se realiza una operación lineal apropiada en
  el método para obtener grados)
* Tipo de transformación: Rotación
* Nodo del grafo: **CabezaR2**

## Extensión de la lente

\begin{center}\includegraphics[width=\textwidth]{../r2_grado2.png}\end{center}

* Clase: `ProjR2`
* Métodos: `R2::extender_proj`, `CabezaR2::extender`, `ProjR2::extender`
* Rango de valores: $[0, 1]$
* Unidades: Valores adimensionales (se realiza una operación lineal apropiada en
  el método para obtener una unidad longitudinal)
* Tipo de transformación: Escalado
* Nodo del grafo: **ProjR2**

## Rotación de los brazos

\begin{center}\includegraphics[width=\textwidth]{../r2_grado3.png}\end{center}

* Clase: `BrazoR2`
* Métodos: `R2::girar_brazos`, `BrazoR2::girar`
* Rango de valores: $[0, 1]$
* Unidades: Valores adimensionales (se realiza una operación lineal apropiada en
  el método para obtener grados)
* Tipo de transformación: Rotación
* Nodo del grafo: **BrazoR2**

## Extensión de los brazos

\begin{center}\includegraphics[width=\textwidth]{../r2_grado4.png}\end{center}

* Clase: `BrazoR2`
* Métodos: `R2::extender_brazos`, `BrazoR2::extender`
* Rango de valores: $[0, 1]$
* Unidades: Valores adimensionales (se realiza una operación lineal apropiada en
  el método para obtener una unidad longitudinal)
* Tipo de transformación: Traslación
* Nodo del grafo: **BrazoR2**
