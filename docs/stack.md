# Stack tecnológico (borrador para la Sección 2 del informe)

## Stack Tecnológico

La solución se implementó como una aplicación web de una sola página (*single-page application*), publicada en GitHub Pages. El usuario objetivo opera el laboratorio desde un navegador, sin instalar software ni depender de los desarrolladores. Se eligió esta plataforma para cumplir el requisito de un enlace directo y funcional.

| Capa | Tecnología | Función en el sistema |
|---|---|---|
| Instrumentación | Sensor digital BH1750 (I2C, módulo GY-302) | Mide la iluminancia en lux, con resolución de 1 lx y rango de 1 a 65 535 lx. |
| Firmware | C++ para Arduino (Arduino IDE), librerías `Wire` y `BH1750` | Lee el sensor en modo continuo de alta resolución y envía una lectura por línea por USB serial (9600 baudios, ~10 Hz). |
| Comunicación | Web Serial API del navegador | Recibe el flujo serial del Arduino directamente en la página, sin intermediarios. |
| Motor de datos | JavaScript (ES2020) | Calibra el cero, filtra con la media de 10 lecturas, calcula la estadística por distancia y ajusta el modelo por mínimos cuadrados (k, R² y exponente n). |
| Simulación | JavaScript: generador de ruido gaussiano (Box-Muller) | Genera lecturas con I = k/d² más luz ambiente y ruido configurable. Permite operar el laboratorio sin hardware. |
| Visualización | SVG nativo generado por código | Muestra el gráfico I vs. d con barras de desviación estándar y la curva ajustada, la tabla de resultados y los indicadores. |
| Interfaz | HTML5 + CSS3 | Interfaz responsiva en tres pantallas (Configuración, Captura, Resultados), con tema claro y oscuro. |
| Despliegue y versiones | Git + GitHub + GitHub Pages | Control de versiones, trazabilidad de commits por rol y hosting público por HTTPS. |
| Prototipado previo | Tinkercad | Simulación del circuito LDR (plan de contingencia) antes del montaje físico. |

La aplicación no usa librerías externas. Los cálculos y los gráficos están programados directamente. Por eso funciona sin conexión una vez cargada y no depende de servicios de terceros.

## Cambio respecto de la Ficha MVP (Semana 5)

En la Semana 5 se proyectó una interfaz local en Python (NumPy, Matplotlib y PySerial). En la integración se migró el motor de datos y la visualización a JavaScript en el navegador, por tres razones:

1. **Autonomía del usuario:** el estudiante abre un enlace y no tiene que instalar Python ni sus librerías.
2. **Enlace funcional para la evaluación:** la guía exige un link directo a la interfaz activa, y el modo simulación permite recorrer el flujo completo sin hardware.
3. **Equivalencia funcional:** la Web Serial API reemplaza a PySerial y los cálculos estadísticos son los mismos que se planificaron con NumPy (media, desviación estándar, regresión y R²).

## Viaje del dato (para el diagrama de bloques)

```
Fuente de luz (LED) ──luz──▶ BH1750 ──I2C──▶ Arduino Uno ──USB serial "123.5\n"──▶ Navegador (Web Serial API)
                                                                                          │
                     [Modo simulación: I = k/d² + ambiente + ruido] ──────────────────────┤
                                                                                          ▼
                                     Motor de datos: calibración de cero → media de 10 lecturas
                                     → 5 repeticiones × 5 distancias → media / desv. est.
                                     → ajuste k por mínimos cuadrados → R², exponente n, error %
                                                                                          ▼
                                     Interfaz: gráfico I vs. d + curva ajustada, tabla, indicadores,
                                     conclusión automática
```
