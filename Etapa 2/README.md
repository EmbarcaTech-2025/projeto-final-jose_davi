# Projeto Final: Etapa 2 - EmbarcaTech 2025 - **Sistema Inteligente para Ambientes Sensíveis/Críticos**

Autor: **Davi Henrique Vieira Lima e José Augusto Alves de Moraes**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, agosto de 2025

---

### *Uma Solução Integrada de Controle de Acesso Físico com Registro de Auditoria e Sensores Ambientais*

---

## **Introdução**

Tendo como base a descrição do sistema definida no [documento da 1° etapa](<../Etapa 1/README.md>)
do projeto final da segunda fase do EmbarcaTech 2025, foram elaborados os diagramas a seguir, os quais descrevem de forma detalhada a estrutura e o funcionamento do sistema que será implementado, especificando a arquitetura do sistema.

Esta documentação tem como objetivo guiar, formalizar e padronizar o desenvolvimento do projeto, permitindo uma avaliação mais precisa, bem como a reprodutibilidade por terceiros interessados.

---

## **Arquitetura do Sistema**
A arquitetura do sistema foi desenvolvida com foco na modularidade e na clareza, visando atender de forma eficiente aos requisitos funcionais e não-funcionais do projeto. Para proporcionar uma compreensão completa e integrada, a arquitetura é apresentada sob três perspectivas distintas e complementares: a organização do hardware, a decomposição em blocos funcionais e o fluxo lógico do software.

O **Diagrama de Hardware** detalha os componentes eletrônicos utilizados e suas interconexões físicas, estabelecendo a base material do sistema. Já o **Diagrama de Blocos Funcionais** abstrai o hardware para uma visão lógica, dividindo o sistema em módulos com responsabilidades específicas. Por fim, o **Fluxograma de Software** ilustra a sequência de operações e as decisões que governam o comportamento do sistema, desde a inicialização até o fim da operação.

---

## **Diagrama de Hardware**
O sistema embarcado apresentado adota uma **arquitetura distribuída**, composta por dois módulos BitDogLab, nomeadas **Mestre** e **Escravo**, que operam em conjunto, interligados por meio do protocolo UART. Essa abordagem modular permite uma clara divisão de tarefas, onde o módulo mestre é responsável pelo controle de acesso e interação com o usuário, enquanto o módulo escravo gerencia o armazenamento de dados e a coleta de informações ambientais.

O **módulo BitDogLab (Mestre)** é o cérebro do controle de acesso. Ele se comunica com um Módulo Leitor RFID-RC522 via SPI, que é responsável por detectar a aproximação dos cartões RFID e extrair suas informações. A interação com o usuário é feita através de um **Display OLED (SSD1306)**, conectado via I2C, que exibe instruções e feedback. Para sinalização sonora e visual, o módulo mestre controla um **Buzzer** e um **LED RGB** através de GPIO.

A segurança física do ambiente é controlada por uma **Fechadura Solenoide Eletrônica - 12V**. Essa fechadura é acionada por um **Módulo Relé 5V**, que por sua vez é controlado pelo módulo mestre via GPIO. A alimentação da fechadura é fornecida por uma **Fonte 12V**, conectada através de um **Adaptador P4 Fêmea com Borne**, garantindo a energia necessária para sua operação.

O **módulo BitDogLab (Escravo)** é dedicado ao monitoramento ambiental e ao registro de auditoria. Ele se comunica com o módulo mestre via UART. Para o armazenamento persistente dos registros de acesso, o módulo escravo utiliza um **Cartão SD**, conectado via SPI através de um **Conector IDC**.

O monitoramento das condições ambientais é realizado por um conjunto de sensores conectados ao módulo BitDogLab (Escravo) através de um **I2C Extender**, que permite a conexão de múltiplos dispositivos I2C. Os sensores utilizados são:

* **BMP280**: para medição de temperatura e pressão atmosférica.

* **AHT10**: para aferição da umidade do ambiente.

* **BH1750**: para captar os níveis de luminosidade.

Esses dados são cruciais para garantir a integridade do ambiente sensível/crítico e são coletados e, posteriormente, enviados pelo módulo escravo para uma interface externa via conectividade sem fio (Wi-Fi), conforme descrito nos requisitos anteriormente.

Essa organização do hardware garante uma arquitetura robusta e modular, com uma clara separação de responsabilidades entre os microcontroladores, otimizando o processamento e assegurando que o sistema atenda de forma confiável às suas funções de controle de acesso, auditoria e monitoramento ambiental.

O diagrama apresentado ilustra de maneira clara as conexões entre os componentes físicos, bem como os protocolos de comunicação utilizados:

![Diagrama de Hardware](./imgs/Diagrama_de_Hardware.png)

---

## **Blocos Funcionais**
Como foi mencionado anteriormente, a arquitetura do sistema foi projetada de forma modular para garantir clareza, escalabilidade e manutenibilidade. Dessa forma, cada bloco funcional possui uma responsabilidade específica no fluxo de operação, sendo o sistema coordenado por uma arquitetura de processamento distribuída entre dois microcontroladores. Essa divisão permite um melhor desempenho e organização das tarefas.

A seguir é explicada a funcionalidade de cada bloco:

- **Módulo de Controle de Acesso**: Composto pelo Leitor RFID-RC522, este bloco é a principal interface de identificação do sistema. Sua função é detectar a aproximação de um cartão, ler suas informações de identificação e os dados criptográficos, e enviá-los ao Módulo de Processamento Central para validação. É o ponto de partida para qualquer operação de entrada ou saída do ambiente.

- **Módulo de Feedback**: Consiste na interface de saída de informações para o usuário. Composto pelo Display OLED, LED RGB e Buzzer, este bloco fornece retornos visuais e sonoros, exibindo status da operação, instruções e alertas.

- **Módulo de Atuação Física**: Este módulo é responsável pela resposta física do sistema após a autenticação. É constituído pela Fechadura Solenoide, pelo Módulo Relé e pela Fonte de 12V. Ao receber um comando de acesso autorizado do processador central, ele aciona o relé, que por sua vez energiza a fechadura, permitindo a abertura da porta.

- **Módulo de Dados do Ambiente**: Este módulo é constituído pelos sensores BMP280 (temperatura e pressão), AHT10 (umidade) e BH1750 (luminosidade). Sua função é monitorar continuamente as condições físicas do local, fornecendo dados essenciais que são enviados via Módulo de Conectividade para garantir a integridade do ambiente.

- **Módulo de Armazenamento**: Responsável por guardar os dados de inventário em um Cartão SD. Este módulo garante a persistência das informações, permitindo que o sistema opere de forma offline e mantenha um registro seguro de todas as transações.

- **Módulo de Conectividade**: Utilizando a capacidade Wi-Fi dos microcontroladores, este módulo permite que o sistema se comunique com a rede. Ele é usado pelo Módulo de Processamento Central para obter a data e hora via NTP (garantindo a precisão dos registros) e pelo Módulo de Processamento Secundário para enviar os dados ambientais via protocolo MQTT para uma interface de monitoramento remoto.

- **Módulo de Processamento Secundário**: Neste bloco está o segundo microcontrolador BitDogLab (Escrava), que atua como um processador dedicado para tarefas de suporte. Ele é responsável por gerenciar o Módulo de Dados do Ambiente, coletando as informações dos sensores, e por controlar o Módulo de Armazenamento, recebendo os dados do processador central e gravando-os no Cartão SD.

- **Módulo de Processamento Central**: Representado pelo microcontrolador BitDogLab (Mestre), este bloco funciona como o núcleo do sistema de acesso. Ele recebe os dados do Módulo de Controle de Acesso, executa a lógica de autenticação criptográfica, comanda os Módulos de Atuação Física e de Feedback, e envia os dados do evento para o processador secundário registrar.

A imagem a seguir explicita de forma visual os blocos funcionais do projeto:

![Blocos Funcioanais](./imgs/Blocos_Funcionais.png)

---

## **Protocolos de Comunicação**
A comunicação eficiente entre os diversos componentes é um pilar fundamental da arquitetura distribuída do sistema. Diante disso, os principais protocolos utilizados são:

* **UART (Universal Asynchronous Receiver/Transmitter)**: Este protocolo de comunicação serial assíncrona é empregado para a interconexão entre os dois microcontroladores BitDogLab Mestre e BitDogLab Escrava. 

* **SPI (Serial Peripheral Interface)**: O protocolo SPI é utilizado para a comunicação de alta velocidade entre os microcontroladores e periféricos que exigem maior taxa de transferência de dados. No projeto, o SPI conecta o BitDogLab Mestre ao Módulo Leitor RFID-RC522, garantindo a leitura rápida das informações dos cartões RFID. Além disso, o BitDogLab Escrava utiliza SPI para interagir com o Cartão SD, permitindo o armazenamento e recuperação eficientes dos logs de auditoria.

* **I2C (Inter-Integrated Circuit)**: O I2C é um protocolo serial síncrono que se destaca pela sua capacidade de interligar múltiplos dispositivos com apenas dois fios (SDA e SCL), simplificando a fiação. Ele é empregado em duas principais áreas do projeto:
    - No BitDogLab Mestre, o I2C é utilizado para a comunicação com o Display OLED (SSD1306), que exibe as informações e feedback ao usuário.

    - No BitDogLab Escrava, o I2C é fundamental para a coleta de dados ambientais. Um I2C Extender é utilizado para expandir a capacidade de conexão, permitindo que os sensores BMP280 (temperatura e pressão), AHT10 (umidade) e BH1750 (luminosidade) se comuniquem com o microcontrolador de forma eficaz.

* **GPIO (General Purpose Input/Output)**: Os pinos GPIO são utilizados para o controle direto e simples de dispositivos que não requerem protocolos complexos, funcionando como uma interface de ligar/desligar ou para a transmissão de sinais digitais básicos. No projeto, os GPIOs são empregados pelo BitDogLab Mestre para:
    - Controlar o Módulo Relé 5V, que por sua vez aciona a Fechadura Solenoide Eletrônica - 12V.
    - Acionar o Buzzer para feedback sonoro.
    - Gerenciar o LED RGB para feedback visual.

* **Wi-Fi**: A conectividade Wi-Fi, intrínseca aos módulos Raspberry Pi Pico W, é crucial para as capacidades de rede do sistema. Ela é utilizada pelo BitDogLab Mestre para realizar requisições NTP (Network Time Protocol) a servidores externos, garantindo que o sistema obtenha a data e hora reais para carimbar os registros de acesso com precisão. A BitDogLab Escrava utiliza o Wi-Fi para enviar os dados ambientais coletados via protocolo MQTT para uma interface de monitoramento remoto, permitindo a telemetria em tempo real das condições do ambiente.

---

## **Fluxograma do Software**

O diagrama a seguir demonstra o fluxo de processos realizados pelo sistema, mostrando uma
abstração do que será implementado em software. No geral haverão dois tipos de processos
executados pelo sistema, processos com input do usuário representados por retângulos azuis
e processos sem input do usuário representados por retângulos brancos.

Os processos que fornecem algum tipo de feedback para o usuário são realizadas pela placa escrava
utilizando os inputs e dados coletados da placa mestre usando a comunicação I2C, essa processo de
comunicação entre as placas foi suprimido no fluxograma por simplicidade.

![Fluxograma de Software](./imgs/Fluxograma_de_Software.png)

---

## **Considerações Finais**
Portanto, é evidente que foi apresentada uma arquitetura técnica do sistema de controle de estoque, estabelecendo um plano de implementação claro e robusto. A estrutura modular, detalhada através do diagrama de hardware, dos blocos funcionais e do fluxograma de software, foi projetada para atender a todos os requisitos, garantindo escalabilidade e manutenibilidade.

O projeto se mostra tecnicamente viável e com grande potencial para garantir o controle de acesso, a auditoria confiável e o monitoramento das condições ambientais de ambientes sensíveis/críticos, oferecendo um caminho bem definido para o desenvolvimento de uma ferramenta eficiente e alinhada às necessidades do mercado.

