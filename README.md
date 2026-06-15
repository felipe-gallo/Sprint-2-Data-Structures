
# Sistema Inteligente de Gerenciamento de Recarga

## Sobre o Projeto

Este projeto foi desenvolvido em linguagem C com o objetivo de simular o funcionamento de uma estação inteligente de recarga para veículos elétricos. O sistema permite o gerenciamento de múltiplas sessões de carregamento, controle de energia, aplicação de tarifas dinâmicas, geração de relatórios e simulação de comunicação com uma plataforma externa.

A proposta do projeto é representar situações que podem ocorrer em uma estação de recarga real, onde vários veículos podem estar carregando simultaneamente, exigindo controle de potência, gerenciamento de demanda e monitoramento das sessões ativas.

---

## Funcionalidades

O sistema possui um menu interativo que permite ao usuário:

* Iniciar uma nova sessão de recarga;
* Consultar as sessões cadastradas;
* Finalizar uma sessão de recarga;
* Gerar relatórios gerais do sistema;
* Encerrar a execução do programa.

Além disso, o sistema realiza automaticamente o controle da potência utilizada, calcula o valor da recarga e simula a comunicação com uma plataforma externa.

---

## Estruturas Utilizadas

Para organizar os dados foi utilizada uma estrutura chamada `Sessao`, responsável por armazenar todas as informações relacionadas a uma recarga.

Nessa estrutura são armazenados dados como:

* Identificação da sessão;
* Nome do cliente;
* Veículo cadastrado;
* Tipo de recarga;
* Nível atual da bateria;
* Nível desejado da bateria;
* Potência utilizada;
* Energia consumida;
* Valor calculado da recarga;
* Horário da sessão;
* Status da recarga.

As sessões são armazenadas em um vetor de estruturas, permitindo que várias recargas sejam gerenciadas simultaneamente.

```c
Sessao sessoes[MAX];
```

Essa abordagem facilita a organização dos dados e o controle das sessões cadastradas durante a execução do programa.

---

## Controle de Potência

O sistema realiza o monitoramento da potência total utilizada pelas sessões ativas.

Foi definido um limite máximo de potência para o sistema. Quando a soma das potências ultrapassa esse valor, a potência das sessões ativas é reduzida automaticamente, simulando um mecanismo inteligente de controle de demanda energética.

Essa funcionalidade permite representar situações em que muitos veículos estão conectados ao mesmo tempo e a estação precisa distribuir melhor a energia disponível.

---

## Tarifação Dinâmica

O cálculo do valor da recarga é realizado de forma dinâmica.

O sistema considera diferentes fatores para definir a tarifa aplicada, como:

* Horário da recarga;
* Tipo de recarga escolhido;
* Demanda atual de energia.

Com isso, o valor final da recarga pode variar de acordo com as condições de utilização do sistema, simulando um modelo de cobrança mais próximo da realidade.

---

## Simulação de Integração

O projeto também simula a comunicação com uma plataforma externa.

Sempre que uma sessão é iniciada ou finalizada, o sistema exibe mensagens representando o envio e o recebimento de informações. Essa comunicação foi inspirada em protocolos utilizados em estações de recarga, como OCPP e MODBUS.

Embora seja uma simulação realizada apenas por meio de mensagens no terminal, ela representa a troca de dados entre a estação de carregamento e um sistema central de gerenciamento.

---

## Funcionamento do Sistema

Ao iniciar uma nova sessão, o usuário informa os dados necessários para a recarga. O sistema então define automaticamente a potência de acordo com o tipo de carregamento escolhido:

* Recarga Normal: 11 kW
* Recarga Rápida: 22 kW

Após o cadastro da sessão, o sistema calcula a energia consumida, aplica a tarifa correspondente e registra todas as informações para futuras consultas.

As sessões permanecem armazenadas até serem finalizadas pelo usuário, permitindo o gerenciamento de múltiplos carregamentos ao mesmo tempo.

---

## Relatórios

O sistema possui uma funcionalidade de geração de relatórios que apresenta informações gerais sobre as sessões cadastradas.

Entre os dados exibidos estão:

* Quantidade total de sessões;
* Número de sessões ativas;
* Energia total consumida;
* Valor total arrecadado;
* Potência total em utilização.

Essas informações permitem acompanhar o desempenho geral da estação e monitorar o uso dos recursos disponíveis.

---

## Conceitos Aplicados

Durante o desenvolvimento do projeto foram utilizados diversos conceitos da linguagem C, incluindo:

* Estruturas (`struct`);
* Vetores;
* Funções;
* Estruturas de decisão (`if` e `switch`);
* Estruturas de repetição (`for`);
* Manipulação de dados;
* Modularização do código;
* Simulação de processos reais;
* Controle de múltiplas sessões em memória.
