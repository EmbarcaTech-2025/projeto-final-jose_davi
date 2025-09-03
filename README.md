# Projeto Final: Sistema de Sensoriamento e Controle de Acesso a Ambientes - EmbarcaTech 2025

Autor: **Davi Henrique Vieira Lima e José Augusto Alves de Moraes**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, agosto de 2025

---

## **Sobre o Projeto**

Este projeto se trata de um sistema inteligente para o sensoriamento
e o controle de entrada de ambientes de acesso restrito, como laboratórios
e ambientes industriais em que é importante saber quem está tendo acesso ao local
e quais as condições do ambiente.

Para isso, criamos um sistema que usa um sensor RFID para registrar a entrada e saída
de pessoas, além de sensores de temperatura, pressão e umidade. Os dados do ambiente são
mandados via MQTT para serem visualizados por uma interface Web, enquanto os registros de
entrada e saída são armazenados internamente.

---

## **Bibliotecas Utilizadas**

- [pico-sdk](https://github.com/raspberrypi/pico-sdk)

  Autor: [Raspberry Pi](https://github.com/raspberrypi)

- [no-OS-FatFS-SD-SPI-RPi-Pico](https://github.com/carlk3/no-OS-FatFS-SD-SPI-RPi-Pico/tree/sdio)

  Autor: [Carl J Kugler III](https://github.com/carlk3)

- [Unity](https://github.com/ThrowTheSwitch/Unity)

  Autor: [Throw The Switch](https://github.com/ThrowTheSwitch)

- [Driver AHT10](https://github.com/jrfo-hwit/hlab/tree/main/firmware/c_cpp/examples/3_aht10_i2c_uart0)

  Autor: [Juliano Oliveira](https://github.com/jrfo-hwit)

- [Driver BH1750](https://github.com/jrfo-hwit/hlab/tree/main/firmware/c_cpp/examples/7_bh1750_i2c_uart0)

  Autor: [Juliano Oliveira](https://github.com/jrfo-hwit)

- [Driver BMP280](https://github.com/jrfo-hwit/hlab/tree/main/firmware/c_cpp/examples/4_bmp280_i2c_uart0)

  Autor: [Juliano Oliveira](https://github.com/jrfo-hwit)

---

## **Montagem**

### **Materiais Utilizados**

| Componente        | Quantidade |
| ----------------- | ---------- |
| Raspberry Pico W  | 2          |
| Buzzer            | 1          |
| Cartão SD         | 1          |
| Display OLED      | 1          |
| LED RGB           | 1          |
| Sensor BH1750     | 1          |
| Sensor AHT10      | 1          |
| Sensor BMP280     | 1          |

### **Esquema de Montagem**

---

## **Como Usar**

### **Compilação**

- Com o VSCode e a extensão [Raspberry Pi Pico](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico):

  Cada placa utilizada no projeto, a mestre e a escrava, possui firmware próprio e para isso é necessário
  indicar qual será o alvo mudando a variável *Device* definida no topo do CMakeLists.txt da pasta `src/app`.

  Tendo escolhido o dispositivo desejado basta compilar e passar o código para a placa utilizando a extensão
  oficial da Raspberry Pi Pico para o VScode.

- Pela linha de comando:

  É possível compilar o projeto utilizando apenas a linha de comando utilizando as ferramentas *cmake*, *ninja*
  e, opcionalmente, o *just*. Caso possua o *just* basta rodar o comando `just build MASTER` para compilar o
  firmware da placa mestre ou `just build SLAVE` para a placa escrava. Caso o *just* não esteja instalado basta
  copiar os comandos definidos no *justfile* presente na raiz do repositório, substituindo `{{ device }}` por `MASTER`
  ou `SLAVE`.

  Tendo compilado o projeto, o binário compilado pode ser passado para a placa utilizando o comando
  `picotool load -f build/src/app/projeto_final.elf`.

### **Instruções de Uso do Sistema**

---

## **Imagens e Vídeo Demonstrativos**

---
