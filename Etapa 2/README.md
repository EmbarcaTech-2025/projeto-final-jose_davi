# Projeto Final: Etapa 2 - EmbarcaTech 2025

Autor: **Davi Henrique Vieira Lima e José Augusto Alves de Moraes**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, agosto de 2025

---

## **Introdução**

Tendo como base a descrição do sistema definida no [documento da 1° etapa](<../Etapa 1/README.md>)
do projeto final da segunda fase do EmbarcaTech 2025, foram elaborados os diagramas a seguir, os quais descrevem de forma detalhada a estrutura e o funcionamento do sistema que será implementado, especificando a arquitetura do sistema.

Esta documentação tem como objetivo guiar, formalizar e padronizar o desenvolvimento do projeto, permitindo uma avaliação mais precisa, bem como a reprodutibilidade por terceiros interessados.

---

## **Arquitetura do Sistema**
A arquitetura do sistema foi desenvolvida com foco na modularidade e na clareza, visando atender de forma eficiente aos requisitos funcionais e não-funcionais do projeto. Para proporcionar uma compreensão completa e integrada, a arquitetura é apresentada sob três perspectivas distintas e complementares: a organização do hardware, a decomposição em blocos funcionais e o fluxo lógico do software.

O **Diagrama de Hardware** detalha os componentes eletrônicos utilizados e suas interconexões físicas, estabelecendo a base material do sistema. Já o **Diagrama de Blocos Funcionais** abstrai o hardware para uma visão lógica, dividindo o sistema em módulos com responsabilidades específicas, como captura de imagem, interface com o usuário e conectividade. Por fim, o **Fluxograma de Software** ilustra a sequência de operações e as decisões que governam o comportamento do sistema, desde a inicialização até o fim da operação.

---

## **Diagrama de Hardware**
O sistema embarcado apresentado adota uma **arquitetura distribuída**, composta por **dois módulos BitDogLab** que operam em conjunto na configuração mestre-escravo, interligados por meio do protocolo I2C. Essa abordagem modular permite uma clara divisão de tarefas, onde o módulo mestre é responsável pela coleta de dados e interação com o usuário, enquanto o módulo escravo gerencia o armazenamento e o feedback ao usuário.

Uma das principais entradas do sistema é realizada por um **Teclado Matricial 4x4**, conectado ao módulo **BitDogLab (Mestre)** via GPIO, utilizando um conector IDC. Esse periférico é fundamental para a interação do usuário, permitindo a inserção da quantidade de produtos, a seleção entre adicionar ou remover itens do estoque e a requisição de dados ambientais.

O monitoramento das condições de armazenamento é realizado por um conjunto de sensores conectados ao **módulo BitDogLab (Mestre)** através de um **IDC Extender** e do barramento I2C. Os sensores utilizados são:

* **BMP280**: para medição de temperatura e pressão atmosférica.

* **AHT10**: para aferição da umidade do ambiente.

* **BH1750**: para captar os níveis de luminosidade.
Esses dados são cruciais para garantir a qualidade do armazenamento e permitir que o usuário tome ações preventivas.

Todos os dados capturados e os comandos inseridos no módulo mestre são enviados para o módulo **BitDogLab (Escravo)** através da comunicação I2C. Este módulo atua como o controlador secundário, responsável por executar as tarefas de armazenamento e notificação.

Para o armazenamento persistente dos dados de estoque, o módulo BitDogLab (Escravo) utiliza um **Cartão SD**, conectado via protocolo SPI por meio de um conector IDC. Isso garante que o sistema possa operar de forma autônoma, registrando todas as transações e mantendo a integridade do inventário mesmo em caso de falha de comunicação com um servidor externo.

A interface visual com o usuário é provida por um **Display OLED (SSD1306)**, conectado ao módulo escravo via I2C. Esse display exibe informações relevantes, como instruções de operação, status do sistema, quantidade de itens e os dados ambientais coletados pelos sensores.

Adicionalmente, o módulo **BitDogLab (Escravo)** controla dois dispositivos de feedback conectados via GPIO:

* Um **LED RGB**, utilizado para indicar visualmente os estados do sistema (ex: modo de adição, modo de remoção, sucesso na operação).

* Um **Buzzer**, responsável por emitir sinais sonoros para alertas ou confirmações de ações.

Essa organização do hardware garante uma arquitetura robusta e modular, com uma clara separação de responsabilidades entre os microcontroladores, otimizando o processamento e assegurando que o sistema atenda de forma confiável às suas funções de controle de estoque e monitoramento ambiental.

O diagrama apresentado ilustra de maneira clara as conexões entre os componentes físicos, bem como os protocolos de comunicação utilizados:

![Diagrama de Hardware](./imgs/Diagrama_de_Hardware.png)

---

## **Blocos Funcionais**
Como foi mencionado anteriormente, a arquitetura do sistema foi projetada de forma modular para garantir clareza, escalabilidade e manutenibilidade. Dessa forma, cada bloco funcional possui uma responsabilidade específica no fluxo de operação, sendo o sistema coordenado por uma arquitetura de processamento distribuída entre dois microcontroladores. Essa divisão permite um melhor desempenho e organização das tarefas.

A seguir é explicada a funcionalidade de cada bloco:

- **Módulo de Entrada de Dados**: Composto pelo Teclado Matricial 4x4, este bloco é uma das principais interface para a interação manual do usuário. Através dele, é possível inserir a quantidade de produtos, selecionar a operação (adicionar ou remover) e solicitar a exibição dos dados ambientais.

- **Módulo de Dados do Ambiente**: Este módulo é constituído pelos sensores BMP280 (temperatura e pressão), AHT10 (umidade) e BH1750 (luminosidade). Sua função é monitorar continuamente as condições físicas do local de armazenamento, fornecendo dados essenciais para garantir a qualidade e a conservação do estoque.

- **Módulo de Processamento Secundário**: Representado pelo microcontrolador BitDogLab configurado como mestre, este bloco atua como um concentrador de entradas. Ele é responsável por coletar os dados provenientes do Módulo de Entrada de Dados (quantidade de produtos e operação (Registro ou Retirada)), Módulo de Dados do Ambiente (temperatura, pressão atmosférica, umidade e luminosidade) e Módulo de Conectividade (nome do produto) realizar um pré-processamento e enviá-los de forma estruturada para o processador central.

- **Módulo de Processamento Central**: Neste bloco está o segundo microcontrolador BitDogLab, configurado como escravo, que funciona como o núcleo do sistema. Ele recebe as informações do módulo secundário, executa a lógica de controle de estoque, gerencia o armazenamento local, comanda os periféricos de feedback e coordena a comunicação externa através do módulo de conectividade.

- **Módulo de Armazenamento**: Responsável por guardar os dados de inventário em um Cartão SD. Este módulo garante a persistência das informações, permitindo que o sistema opere de forma offline e mantenha um registro seguro de todas as transações.

- **Módulo de Feedback**: Consiste na interface de saída de informações para o usuário. Composto pelo Display OLED, LED RGB e Buzzer, este bloco fornece retornos visuais e sonoros, exibindo status da operação, instruções, alertas e os dados coletados do ambiente.

- **Módulo de Conectividade**: Utilizando a tecnologia Wi-Fi e o protocolo MQTT, este módulo permite que o sistema se comunique com aplicações externas. Ele é responsável por receber dados, como o nome de um produto, e enviar atualizações sobre o estado do estoque para um servidor central, integrando o dispositivo a um ecossistema maior.

A imagem a seguir explicita de forma visual os blocos funcionais do projeto:

![Blocos Funcioanais](./imgs/Blocos_Funcionais.png)

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

O projeto se mostra tecnicamente viável e com grande potencial para otimizar a gestão de inventários/estoques, oferecendo um caminho bem definido para o desenvolvimento de uma ferramenta eficiente e alinhada às necessidades do mercado.

