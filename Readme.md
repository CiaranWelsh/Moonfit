
---
description: "ODE Model for influenza-induced thymic atrophy" 
stage: "V1, 8/09/2020"
---

Here, you can download the C++ code used in Elfaki, Robert et al. 2020, "Influenza A virus-induced thymus atrophy differentially affects dynamics of conventional and regulatory T cell development" 

Briefly, this is an ODE model for simulating the dynamics of thymic populations during influenza infection.
The Balthyse/ folder contains the model,
	Please refer to this folder for explanations

The Moonfit folder is the library used to perform simulations and optimizations. See Robert et al 2018, "MoonFit, a minimal interface for fitting ODE dynamical models, bridging simulation by experimentalists and customization by C++ programmers"

## Use cases

The details on how to reproduce the simulations of the article are shown in Balthyse/HowToReproduce.docx

## Requirements

C++ compiler, 
Qt environment
QtCreator 
[optional: boost library if you like to use other ODE solvers]
latex is recommended for the automatic generation of simulation reports
