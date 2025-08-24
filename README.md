# Projeto Final: Sistema de Gestão e Monitoramento de Estoques - EmbarcaTech 2025

Autor: **Davi Henrique Vieira Lima e José Augusto Alves de Moraes**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, agosto de 2025

---

## **Sobre o Projeto**

Este projeto se trata de um sistema inteligente para a gestão e monitoramento de estoques.
O projeto possibilita a aferição de fatores importantes para a preservação de certos produtos
como luminosidade, temperatura, pressão e umidade do ambiente. Além disso, o sistema possibilita
o cadastro de produtos num banco de dados interno ao dispositivo, permitindo que seja registrada
a chegada e a retirada de produtos. Por fim, o sistema é capaz de se comunicar utilizando o protocolo
MQTT, enviando os dados coletados a outro dispositivo.

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
