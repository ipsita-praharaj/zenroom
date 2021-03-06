# Zenroom - crypto language VM

[![software by Dyne.org](https://www.dyne.org/wp-content/uploads/2015/12/software_by_dyne.png)](http://www.dyne.org)

[![Build Status](https://travis-ci.org/DECODEproject/zenroom.svg?branch=master)](https://travis-ci.org/DECODEproject/zenroom)

Zenroom is a brand new, small and portable virtual machine for cryptographic operations. Our effort is that of improving people's awareness of how their data is processed by algorithms, as well facilitate the work of developers to create and publish algorithms that can be used both client and server side. The Zenroom VM has no external dependencies, is smaller than 1MB, runs in less than 64KiB memory and is ready for experimental use on many target platforms: desktop, embedded, mobile, cloud and browsers.

## Latest stable release is 0.5.0:
<ul class="center">

<li class="fab fa-node-js"><a href="https://files.dyne.org/zenroom/releases/zenroom-0.5.0-js.zip">NodeJS</a></li>

<li class="fab fa-linux"><a href="https://files.dyne.org/zenroom/releases/zenroom-0.5.0-x86_64_linux.zip">Linux x86 64bit</a></li>

<li class="fab fa-android"><a href="https://files.dyne.org/zenroom/releases/zenroom-0.5.0-armhf.zip">ARM hard-float</a></li>

<li class="fab fa-windows"><a href="https://files.dyne.org/zenroom/releases/zenroom-0.5.0-win64.zip">MS/Windows 64bit</li>

<li class="fab fa-apple"><a href="https://files.dyne.org/zenroom/releases/zenroom-0.5.0-osx.zip">Apple/OSX</li>

<li class="far fa-file-archive"><a href="https://files.dyne.org/zenroom/releases/Zenroom-0.5.0.tar.gz">Source Code</a></li>

<li class="fab fa-github"><a href="https://github.com/decodeproject/zenroom">Git repository</a></li>

<li class="far fa-archive"><a href="https://files.dyne.org/zenroom/">Releases archive</a></li>

</ul>

## Documentation:

<ul class="center"
>
<li class="fas fa-code"><a href="https://zenroom.dyne.org/api">Language Documentation</a><sup>*</sup></li>

<li class="far fa-graduation-cap"><a href="https://zenroom.dyne.org/whitepaper">Zenroom Whitepaper</a></li>

<li class="far fa-hand-point-right"><a href="https://zenroom.dyne.org/demo">Online Demo</a></li>

<li class="far fa-cogs"><a href="https://github.com/DECODEproject/zenroom/wiki">Build Instructions</a></li>

</ul>
<p class="pull-right"><sup>*</sup> = Work in Progress</p>


Zenroom is software in **ALPHA stage** and is part of the [DECODE project](https://decodeproject.eu) about data-ownership and [technological sovereignty](https://www.youtube.com/watch?v=RvBRbwBm_nQ).

<a href="https://decodeproject.eu">
<img src="https://zenroom.dyne.org/img/decode.svg" width="54%"
	alt="DECODE project"></a>

This software aims to make it easy and less error-prone to write **portable** scripts using **end-to-end encryption** inside isolated environments that can be easily made **interoperable**. Basic crypto functions provided include primitives to manage **a/symmetric keys, key derivation, hashing and signing functionalities**.


Zenroom is software inspired by the [language-theoretical security](http://langsec.org) research, it allows to expresses cryptographic operations in a readable scripting language that has no access to the calling process, underlying operating system or filesystem.
<p class="pull-right"><sup>*</sup> = Work in Progress</p>

<a href="http://langsec.org/occupy/">
<img src="https://zenroom.dyne.org/img/InputLanguages.jpg" class="pic"
	alt="No more Turing Completion!" target="_blank"></a>

Zenroom's **restricted execution environment** is a sort of [sandbox](https://en.wikipedia.org/wiki/Sandbox_%28computer_security%29) whose parser is based on LUA's [syntax-direct translation](https://en.wikipedia.org/wiki/Syntax-directed_translation) and has coarse-grained control of computations and memory. The Zenroom VM is designed to "brittle" and exit execution returning a meaningful message on any error.

Zenroom's documentation and examples are being written to encourage a [declarative](https://en.wikipedia.org/wiki/Declarative_programming) approach to scripting, providing functional tools to manipulate efficiently even complex data structures.


<a href="http://langsec.org/occupy/">
<img src="https://zenroom.dyne.org/img/FullRecognition.jpg" class="pic"
	alt="Full Recognition Before Processing!" target="_blank"></a>


The main use case for Zenroom is that of **distributed computing** of untrusted code where advanced cryptographic functions are required, for instance it can be used as a distributed ledger implementation (also known as **blockchain smart contracts**).


![Horizon 2020](https://zenroom.dyne.org/img/ec_logo.png)

This project is receiving funding from the European Union’s Horizon 2020 research and innovation programme under grant agreement nr. 732546 (DECODE).

## Acknowledgements

Copyright (C) 2017-2018 by Dyne.org foundation, Amsterdam

- Designed, written and maintained by <a href="https://jaromil.dyne.org">Denis "Jaromil" Roio</a>

With contributions by Ivan J., Puria Nafisi Azizi, Jordi Coscolla.

Special thanks to Francesca Bria for leading the DECODE project and to George Danezis, Ola Bini, Mark de Villiers and Alberto Sonnino for their expert reviews.

This software includes software components by:

- R. Ierusalimschy, W. Celes and L.H. de Figueiredo (lua)
- Mike Scott and Kealan McCusker (milagro-crypto-c)
- Ralph Hempel (umm_malloc)
- Mark Pulford (lua-cjson)
- Daan Sprenkels (randombytes)

And Lua extensions written and documented by:

- Roland Yonaba (moses)
- Enrique García Cota (inspect)
- Sebastian Schoener (schema)
- Kyle Conroy (finite state machine)
- Scott Lembcke (debugger)
- Michael Lutz and David Manura (matrix and complex)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License version 3
as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this program.  If not, see
<http://www.gnu.org/licenses/>.
