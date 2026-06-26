# SAAESSC V3
**Automatic Data Acquisition System for Supercapacitor Characterization**

## 📌 Overview
The SAAESSC (*Sistema Automático de Aquisição de Dados para Caracterização de Supercapacitores*) is an embedded instrumentation project designed for the automated testing, data acquisition, and characterization of energy storage devices, specifically supercapacitors. 

Version 3 brings a refined, integrated architecture utilizing an STM32 microcontroller and wireless data transmission via Bluetooth, allowing for isolated and precise measurements without tethering to a PC.

## 📂 Repository Structure
* `/STM32_Code/`: Contains the firmware source code, HAL configurations, and project files for the STM32 microcontroller.
* `/PCB/`: Contains the schematics, layouts, and manufacturing files (Gerbers, component IDs, and PDFs) for the hardware design.
* `/Scripts/`: Python/MATLAB scripts for serial data logging, interpolation, and hysteresis area calculations.

## 🔌 Hardware & PCB Design
The hardware architecture of SAAESSC V3 is modular and optimized for precise instrumentation. To minimize noise and improve signal integrity, the PCB design is divided into specific functional blocks:
* **Signal Generation Board (`SignalGen`):** Responsible for generating the controlled stimulus (e.g., precise charge/discharge cycles and specific analog waveforms) applied to the supercapacitor under test.
* **Data Acquisition Board (`Acquisition`):** Handles the high-resolution conditioning and reading of voltage and current responses, interfacing directly with the STM32's ADCs.

## 🚀 How to Use the STM32 Firmware

1. **Prerequisites:** Ensure you have [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) (or your preferred ARM GCC toolchain) installed.
2. **Clone the repository:**
   `git clone https://github.com/gSantiago22/SAAESSC_V3.git`
3. **Open the project:** Navigate to the firmware folder and open the `.ioc` or `.cproject` file in your IDE.
4. **Build and Flash:** Compile the code and flash it onto your STM32 board using an ST-LINK programmer. Ensure your target board matches the MCU selected in the CubeMX project settings.

## 📡 Bluetooth Data Reception

The system transmits characterization data wirelessly via a Bluetooth module connected to the STM32's UART peripheral.

### Setup Instructions:
1. **Pairing:** Power on the system and pair the Bluetooth module with your PC or mobile device.
2. **Serial Port Setup:** Open a Serial Terminal (such as PuTTY, Tera Term, or a custom Python/MATLAB monitoring script).
3. **Connection Configuration:**
   * **Baud Rate:** `115200` *(Adjust based on your specific UART configuration)*
   * **Data Bits:** `8`
   * **Stop Bits:** `1`
   * **Parity:** `None`
4. **Data Format:** The STM32 sends the telemetry (e.g., Timestamp, Voltage, Current) in a comma-separated format. This makes it straightforward to parse the stream in real-time for plotting or to save it as a `.csv` for post-processing characterization.

## 🏫 Acknowledgments
Developed as part of the Scientific Initiation research at the **Federal University of Minas Gerais (UFMG)**.
Supported by **OptMA.lab** (Laboratório de Optrônica e Microtecnologias Aplicadas).
