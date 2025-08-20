# Projeto Final: Etapa 1 - EmbarcaTech 2025

Autor: **Davi Henrique Vieira Lima e José Augusto Alves de Moraes**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, julho de 2025

---

## Descrição do Problema

Atualmente, o controle de estoque é um dos principais desafios enfrentados
por empresas de diversos setores, impactando diretamente a eficiência operacional,
os custos logísticos, a lucratividade e até mesmo a satisfação do cliente.
Um estoque mal gerenciado pode causar desde a falta de produtos essenciais,
comprometendo vendas e a reputação da empresa, até o excesso de mercadorias paradas,
que ocupam espaço, imobilizam capital e geram desperdícios.

Ainda é comum o uso de técnicas manuais, como planilhas eletrônicas e pranchetas,
para a gestão de estoque, o que dificulta o acompanhamento preciso de inventários
sujeitos a flutuações constantes. Essa abordagem torna o processo mais lento,
impreciso e vulnerável a erros humanos, como registros incorretos, perdas por
vencimento e falhas na previsão de demanda, comprometendo a reposição adequada e
gerando prejuízos financeiros consideráveis.

Além disso, a falta de visibilidade em tempo real sobre o estado dos estoques
prejudica a tomada de decisões estratégicas, como a negociação com fornecedores,
o planejamento de compras e a resposta a oscilações de mercado. Em empresas que
operam com grande variedade de itens, como redes varejistas e indústrias, a
complexidade do controle se torna ainda maior.

Diante de um cenário de digitalização acelerada e aumento da competitividade,
torna-se essencial a adoção de sistemas automatizados e inteligentes. Essas
ferramentas não apenas asseguram um controle mais preciso e ágil, como também
permitem previsões de demanda, alertas automáticos de reposição, rastreabilidade
de produtos e redução significativa de perdas e desperdícios.

Portanto, investir na modernização do controle de estoque não é apenas uma escolha
estratégica, mas uma necessidade para a sobrevivência e crescimento sustentável das
empresas no contexto atual.

---

## Proposta

Com o objetivo de mitigar a problemática mencionada, este trabalho propõe o
desenvolvimento de uma solução automatizada para controle de estoque, por meio
de um sistema capaz de receber dados acerca de produtos do estoque e
registrar, de forma precisa, quais itens estão disponíveis e em que quantidade.

O sistema também possibilita a interação com o usuário por meio do mecanismo de 
conectividade, onde o usuário informar o nome do produto que será considerado. Além disso, o usuário tem a sua disposição um periférico que lhe permite, de forma prática e eficiente, o registro da quantidade de um determinado produto e se ele será incluído ou removido do estoque.

Além disso, o sistema utiliza esse mecanismo de conectividade para se comunicar
com um sistema externo, enviando mensagens com informações relevantes
para o gerenciamento do estoque — como a quantidade de itens adicionados ou
retirados, a data e hora da operação, entre outros dados — contribuindo para um
controle mais completo, seguro e integrado.

Por fim, o sistema será capaz de fornecer, ao usuários, dados acerca das condições físicas do ambiente. Entrando em detalhes, essas condições são:
- Temperatura
- Umidade
- Luminosidade
- Pressão
Assim, o sistema também fornece insights cruciais sobre o ambiente de armazenamento, medindo continuamente esses aspectos. Com esses dados em mãos, o usuário pode otimizar a gestão de seu estoque e tomar ações preventivas.

Como conclusão, o desenvolvimento deste sistema representa uma alternativa viável
e eficiente para modernizar o controle de estoque, reduzindo falhas humanas, aumentando
a precisão das informações e promovendo maior integração entre os processos internos e
externos das organizações. Ao aliar tecnologias, a solução proposta demonstra
potencial para atender às demandas de um cenário empresarial cada vez mais dinâmico e
automatizado, contribuindo significativamente para a otimização da gestão de inventário.

---

## Requisitos Funcionais

O sistema deve poder atender os seguintes requisitos funcionais:

- Receber o nome do produto por meio de um mecanismo de conectvidade com o usuário.
- Indicar ao usuário que o nome do produto foi recebido.
- Permitir ao usuário a definição da quantidade de produtos que ele quer adicionar ou remover.
- Indicar ao usuário que a quantidade desejada foi recebida.
- Permitir a interação com usuário para que ele tanto adicione produtos quanto remova produtos.
- Indicar ao usuário, visualmente, se o sistema está operando em modo para adicionar produtos ou para remover produtos.
- Armazenar e atualizar a quantidade de produtos.
- Fornecer dados acerca temperatura, umidade, luminosidade e pressão do ambiente ao usuário.
- Enviar e receber dados sobre o estoque via MQTT.

---

## Requisitos Não-Funcionais

O sistema deve poder atender os seguintes requisitos não-funcionais:

- Confiabilidade: o sistema deve operar de forma estável e previsível.
- Portabilidade: o sistema deve ser portátil, ou seja, que pode ser transferido com facilidade.
- Baixo Consumo de Energia: o sistema deve operar com um baixo consumo de energia.
- Longo Período de Funcionamento: o sistema deve ser capaz de operar de forma robusta por longos períodos.
- Segurança: deve ser garantido a autenticidade e integridade dos dados.
- Escalabilidade: o sistema deve ser capaz de expandir suas funcionalidades e integrar novos módulos.
- Usabilidade: a interface de interação com usuário deve ser fácil e interativa.

---

## Componentes Utilizados

Para possibilitar a satisfação dos requisitos técnicos do sistema serão utilizados
os seguintes componentes, alguns presentes na BitDogLab, outros não:

| Componente        | Quantidade |
| ----------------- | ---------- |
| Buzzer            | 1          |
| Cartão SD         | 1          |
| Display OLED      | 1          |
| LED RGB           | 1          |
| Teclado Matricial | 1          |
| Sensor BH1750     | 1          |
| Sensor AHT10      | 1          |
| Sensor BMP280     | 1          |

Obs.: Para esse projeto, serão utilizadas duas BitDogLabs.

---

## Especificações

A fim de cumprir os requisitos funcionais, o sistema seguirá as seguintes especificações:

- Utilizando o mecanismo de conectividade WI-FI, utilizando o protocolo MQTT, o sistema se inscreve em m tópico específico e recebe o nome do produto que será registrado ou removido pelo usuário.
- Utilizando o teclado matricial, o usuário pode especificar ao sistema se ele quer adicionar ou remover o produto e a quantidade do produto considerado.
- Utilizando o Display OLED será apresentado ao usuário informações sobre o produto, instruções para realizar as diversas operações permitidas pelo sistema, entre outras informações.
- Utilizando a comunicação I2C, a BitDogLab fará o envio desses dados para outra BitDogLab, que apresenta a placa adaptadora de SD Card.
- O cartão SD será utilizado a fim de armazenar informações sobre o estoque local, permitindo a operação do sistema mesmo em caso de queda do servidor central.
- O sistema enviará feedbacks extras, além do Display OLED, ao usuário acerca de suas operações por meio de um buzzer e um LED RGB. Exemplo: após a leitura do QR Code, o sistema indicará que o produto foi identificado por meio do som do buzzer e a cor verde do LED RGB.
- Também por meio do módulo Wi-Fi da BitDogLab, utilizando o protocolo MQTT, o sistema será capaz de enviar e receber dados acerca da quantidade de determinado produto no estoque, número de produtos adicionados ou retirados, entre outros.
- A temperatura (Sensor BMP280), umidade (Sensor AHT10), luminosidade (Sensor BH1750) e pressão (Sensor BMP280) serão obtidas por meio de seus respectivos sensores e apresentados ao usuário por meio do display oled mediante uma requisição do usuário utilizando o teclado matricial.
