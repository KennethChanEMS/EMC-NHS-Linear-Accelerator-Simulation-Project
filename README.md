# NHS Medical Linear Accelerator Simulation

This project is the simulation for the Exeter Math Certicate NHS Linear Accelerator research in which out team did research on Medical use Linear Accelerators (LinAc) for its structure and measures for dosing

## Geant4

Seen in our report ________, we used Geant4 as our way to simulate the process from the generation of photons (gamma x-rays) to the detection of a Ionisation Chamber (see report). This is due to the extensive physics libraries included in the program.

## How to use

1. Download bash (if windows is used download WSL)
2. Download cmake, and qt5
3. Download Geant4 packages by following the instruction in their home page
4. Create a build folder and input cmake .. inside the directory in bash
5. Go to src folder and open config.cc, there you can change field_size, Source to Surface Distance and Beam energy
6. Input make
7. Input ./linacv2 <br>
By following these steps, you should see a graphic window just press the start button and it will run, the data will be stored in data.csv
