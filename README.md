# Bachelor thesis project

# Video: [youtube demonstration for motor starting](https://www.youtube.com/watch?v=OzBrSzkHfI8&ab_channel=Ataraxy)

# Sensorless BLDC Controller using BEMF and Zero Crossing Point (ZCP) Detection

# Hardware: https://github.com/vladBaciu/-HW_2019_KiNonPCB-Sensorless-BLDC

This work aims to control a BLDC (brushless DC motor) using the back-electromotive force (BEMF) of the unpowered coil as feedback. To achieve this goal, specific hardware topologies were simulated, tested, and implemented. The software part was developed on an ARM Cortex M4 architecture, and the code complies with the AUTOSAR (AUTomotive Open System ARchitecture) standard used in the automotive industry.

# 1. Introduction

This work focuses on designing an embedded system for sensorless control of a BLDC motor using the BEMF (back-electromotive force) method. Since sensorless control is typically used in applications with a fixed motor load in the industry, this work tests the behavior of a 36V, 300W motor under various loads and low-speed operation.

Generally, BLDC motor control employs six-step commutation. Each phase conducts for 120°, and at any given time, only two phases are active. This allows the detection of BEMF on the third inactive phase, but for zero-crossing point detection, access to the virtual node of the motor is required, serving as the reference for the BEMF signal. As the virtual node is not directly accessible, it is created using a network of resistors. Figure 1 shows the construction of the virtual node and the zero-crossing point detection of BEMF.

![image](https://user-images.githubusercontent.com/24388880/153602152-070da2fc-dd5c-455d-8a6a-2e212eee148e.png)

**Fig. 1 Implementation of the virtual node and zero-crossing point detection of BEMF**

From the relation below, it can be observed that the BEMF amplitude is proportional to the rotor speed, implying a lower speed limit for BEMF detection in motor control.

**V<sub>BEMF</sub> = B * L * v**

Since the BEMF amplitude is low during startup, and the detection circuit cannot signal the zero-crossing point, an experimental startup sequence was determined. This sequence was implemented in software using a lookup table read with the help of software interrupts. As the rotor position is unknown during startup, a software routine was implemented to position the rotor at a predefined position relative to the stator.

![image](https://user-images.githubusercontent.com/24388880/153603005-ef8fe3c8-750e-42d6-a287-8a6d75c07936.png)

**Fig. 2a Simulink Modeling for Sensorless Control**

For motor control, an inverter was designed using six N-type MOSFET transistors. Bootstrap IR2101 command drivers with bootstrap capacitors were used to command the upper transistors of the inverter. Although using P-type MOSFET transistors would be an easier implementation, their on-state resistance is higher than that of N-type transistors due to the majority carrier type in the P-region.

![image](https://user-images.githubusercontent.com/24388880/153603072-65890214-c291-4284-84a8-d4f80b8e6f94.png)

**Fig. 2b BEMF Voltage and Zero-Crossing Point on each phase. Simulink Simulation**

![image](https://user-images.githubusercontent.com/24388880/153603184-962c2906-b3e2-43b8-b40d-ecfc5195c557.png)

**Fig. 3 AUTOSAR Standard-based Software Architecture**

# 3. Results

Currently, the system can sensorlessly control a 36V, 350W hoverboard motor using BEMF detection, as highlighted in Figure 14. The electronic modules were designed in KiCad and printed using the toner transfer method to fix the circuit image on the copper laminate. Signal visualization and debugging were done using the Hantek6022BE oscilloscope together with LabView programming language, where a software driver was developed calling functions from a DLL (Dynamic-link library) provided by the manufacturer.

![image](https://user-images.githubusercontent.com/24388880/153603255-8e72aeb5-21f0-4b49-8d7d-e7eb49b3b4a1.png)

**Fig. 4 Experimental Assembly**

Regarding the zero-crossing point detection of the BEMF signal, analog filters were implemented to filter the 20 kHz PWM signal.

To ensure detection accuracy, Hall sensor outputs were compared with comparator outputs, and the signals had a 30° phase shift.

![image](https://user-images.githubusercontent.com/24388880/153603467-2fdb3206-2092-4eba-92e2-1f12034b9835.png)

**Fig. 5 Hall Output and Comparator Output for Phase B**

Through experimental trials, a table was determined based on which the three phases are actuated.

**Tab. 1 Switching Sequences Based on Comparator Outputs**

![image](https://user-images.githubusercontent.com/24388880/153603622-c824940b-3502-430e-b446-816e3bc04158.png)

In Figure 5, the voltage on phase A with the virtual node as a reference is highlighted. This signal is known in the literature as the third harmonic of the BEMF signal and can be used for zero-crossing point detection of the inverse electromotive force voltage. These methods are called indirect methods of zero-crossing point detection and are used in the industry for low-speed (RPM) motor control. Among the indirect methods are the BEMF integration method, the third harmonic integration method, phase current measurement, and the method using parasitic diodes (Free-Wheeling Diode) for ZCP (zero crossing point) detection.

![image](https://user-images.githubusercontent.com/24388880/153603802-7dbf2648-b808-4ee6-ae4e-e6149e4860f8.png)

**Fig. 5 Voltage on a Phase with the Virtual Node as a Reference**

In Figure 6, after filtering, the reverse electromotive force voltage is asymmetric, leading to an imbalance in ZCP detection. This is due to the chosen motor type, treated as an unknown system due to the lack of catalog information from the manufacturer. ZCP imbalance results in an unstable system component. The paper "Unbalanced ZCP Compensation Method For Position Sensorless BLDC Motor," published in the IEEE Transactions on Power Electronics, Volume 34, Number 4, April 2019, proposes a method to eliminate this drawback. In Figure 7, the reverse electromotive force voltage on a 12V motor was measured, and the zero-crossing point is symmetric and 30° away from the last commutation.

![image](https://user-images.githubusercontent.com/24388880/153603960-ef6a4552-d4cc-4521-a38f-7d00db4db879.png)

**Fig. 6 Zero-Crossing Point Detection**

![image](https://user-images.githubusercontent.com/24388880/153604105-ef760424-524d-4070-a8c4-63920c0fcdb9.png)

**Fig. 7 Zero-Crossing Point Detection. Filtered Signal**

![image](https://user-images.githubusercontent.com/24388880/153604166-9da9df7e-9dde-43fd-a476-22e474416112.png)

**Fig. 8 Balanced BEMF. Unfiltered Signal. Yellow – Phase A, Green – Phase B**

In Figure 9, zero-crossing point detection is highlighted as the PWM signal duty cycle increases during acceleration, and the BEMF is unfiltered.

![image](https://user-images.githubusercontent.com/24388880/153604291-57538fc2-75d9-4f16-a323-4be021ee4e14.png)

**Fig. 9 Zero-Crossing Point Detection During Acceleration. Unfiltered BEMF**

In Figure 10, the voltage of the virtual node, known as the reference node, is highlighted. As can be seen, the reference voltage at the inverter's input is not constant.

![image](https://user-images.githubusercontent.com/24388880/153604401-13f75a84-936f-4718-a3f1-7776164aff5c.png)

**Fig. 10 BEMF Voltage and Virtual Node. Yellow – BEMF, Green – Virtual Node**

In addition to the experimental and educational aspects, the project aimed to create an ESC (Electronic Speed Controller) that adheres to industry standards and can be widely commercialized. Figure 11 presents the electronic module in SMD (surface-mounted device) technology.

![image](https://user-images.githubusercontent.com/24388880/153604481-4e73504c-ae69-445f-b3ba-b4d65bc7333e.png)

**Fig. 11 Physically Realized Module for Commercialization**

For module protection, a 3D case was designed by transforming the 3D files from KiCad into STEP format to export the dimensions of the electronic module. Figures 11 and 12 show the 3D model created in FreeCad.

![image](https://user-images.githubusercontent.com/24388880/153604605-8c82ea52-e4ac-4589-9d25-3ae0a3b21fc3.png)

**Fig. 12 Case Design in FreeCad**

![image](https://user-images.githubusercontent.com/24388880/153604698-e45bb6a8-c942-4c1b-9360-761db2c0397a.png)

**Fig. 13 3D Printed Case**

# 4. Conclusions

As BLDC motors replace brushed motors, sensorless control is of great interest to developers in the automotive, aerospace, and HVAC (heating, ventilation, and air conditioning) fields. Sensor elimination reduces motor production costs and dimensions. The implementation of the project is of interest to companies in the field and constitutes a continuously evolving research area. The project aimed to


# References

Microelctronics, S. T. (2007). Sensorless bldc motor control and bemf sampling methods with st7mc. AN1946 Application Note, 3-5.
Gamazo-Real, J. C., Vázquez-Sánchez, E., & Gómez-Gil, J. (2010). Position and speed control of brushless DC motors using sensorless techniques and application trends. Sensors, 10(7), 6901-6947.

Fürst, S., Mössinger, J., Bunzel, S., Weber, T., Kirschke-Biller, F., Heitkämper, P., ... & Lange, K. (2009, October). AUTOSAR–A Worldwide Standard is on the Road. In 14th International VDI Congress Electronic Systems for Vehicles, Baden-Baden (Vol. 62, p. 5).

Park, J. S., Lee, K. D., Lee, S. G., & Kim, W. H. (2018). Unbalanced ZCP Compensation Method for Position Sensorless BLDC Motor. IEEE Transactions on Power Electronics, 34(4), 3020-3024.

Bakare, M. R. S., & Jain, G. P. (2015). PSOC Based Speed Control of BLDC Motor. Asian Journal For Convergence In Technology (Founded by ISB &M School of Technology)), 1.


