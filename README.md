# 🖧 Protótipo de Sistema P2P com Paradigma Publish/Subscribe em C

## 📘 Descrição do Projeto
Este projeto apresenta um **protótipo simples** de uma rede **Peer-to-Peer (P2P)** desenvolvida em **linguagem C**, que implementa o **paradigma de comunicação assíncrona Publish/Subscribe (Publicar/Inscrever-se)**.

O objetivo é **demonstrar como múltiplos nós (peers)** — atuando simultaneamente como cliente e servidor — podem **trocar mensagens de forma desacoplada** por meio de um sistema baseado em tópicos, **sem a necessidade de um intermediário central**.

---

## 🧩 Conceitos Implementados

### 🔹 Peer-to-Peer (P2P)
A arquitetura **P2P** é simulada permitindo que múltiplas instâncias do programa (cada uma representando um *peer*) sejam executadas independentemente em terminais separados.  
Cada peer pode:
- **Publicar mensagens** em tópicos;
- **Inscrever-se** para receber mensagens de tópicos de interesse.  

Isso caracteriza o comportamento **descentralizado e colaborativo** de uma rede P2P.

### 🔹 Publish/Subscribe
O paradigma **Publish/Subscribe** é o núcleo da comunicação entre os peers.

- **Publicadores (Publishers):** Qualquer peer pode publicar mensagens em um tópico, sem conhecer seus destinatários.  
- **Inscritos (Subscribers):** Qualquer peer pode se inscrever em um ou mais tópicos e receber todas as mensagens publicadas neles.

### 🔹 Inter-Process Communication (IPC)
Como cada peer é um processo independente, a comunicação é simulada por meio de um **arquivo compartilhado** (`message_board.txt`), que atua como um **mural público de mensagens**.  
Os peers:
- Escrevem no mural ao publicar mensagens;
- Leem o mural para verificar novas mensagens em tópicos assinados.

---

## ⚙️ Funcionalidades

- **Publicar mensagens:** Envia mensagens para tópicos específicos.  
- **Inscrever-se em tópicos:** Adiciona dinamicamente um peer como inscrito em um tópico.  
- **Cancelar inscrição:** Permite sair de um tópico.  
- **Visualizar mensagens:** Exibe mensagens novas de tópicos assinados.  
- **Gerenciamento dinâmico:** Criação de tópicos e inscrições sem limites fixos.  

---

## 🗂️ Estrutura do Projeto

```
.
├── Makefile             # Compilação automatizada (Linux/macOS)
├── main.c               # Ponto de entrada do programa (interface principal do Peer)
├── subscriber.c         # Implementação da lógica Publish/Subscribe (leitura/escrita)
├── subscriber.h         # Cabeçalho com definições de estruturas e funções
├── message_board.txt    # Arquivo de IPC (criado na primeira publicação)
└── peer                 # Executável gerado após compilação
```

---

## 🧱 Como Compilar e Executar

### 🔧 Pré-requisitos
- Compilador C (ex: **GCC**).  
  - Para Windows, recomenda-se o **MinGW-w64**.

### 💻 Compilação

**Opção 1 — Usando Makefile (Linux/macOS):**
```bash
make
```

**Opção 2 — Manualmente com GCC (Windows ou sem make):**
```bash
gcc -o peer main.c subscriber.c -Wall
```

Ambos os métodos geram o executável `peer` (ou `peer.exe` no Windows).

---

## 🚀 Execução da Simulação

A simulação deve ser executada com **um terminal para cada peer**.  
Para melhor visualização, utilize ao menos **três terminais**:

**Terminal 1:**
```bash
./peer PeerA
```

**Terminal 2:**
```bash
./peer PeerB
```

**Terminal 3:**
```bash
./peer PeerC
```

---

## 💬 Exemplo de Uso

### 🟢 Estado Inicial
- `PeerA` já está inscrito no tópico **Esportes**.  
- `PeerB` já está inscrito no tópico **Música**.  

### 1️⃣ Publicar uma Mensagem
No terminal do `PeerC`, selecione a opção **1 (Publicar)**:

```
Tópico: Esportes
Mensagem: Grande final hoje à noite!
```

### 2️⃣ Verificar o Recebimento
- No `PeerA`, selecione a opção **4 (Ver minhas mensagens)** → a mensagem será exibida.  
- No `PeerB`, nenhuma mensagem aparecerá (não está inscrito em "Esportes").  

### 3️⃣ Inscrição Dinâmica
No `PeerB`, selecione **2 (Inscrever-se)** e inscreva-se no tópico `Esportes`.

### 4️⃣ Nova Publicação
Se o `PeerC` publicar novamente em `Esportes`, **PeerA** e **PeerB** receberão a nova mensagem.

---

## 🧠 Possíveis Extensões
- Implementar comunicação via **sockets TCP/UDP** em vez de arquivo compartilhado.  
- Adicionar **persistência de mensagens** com timestamps.  
- Criar **interface de monitoramento** dos tópicos ativos.  

---

## 🧑‍💻 Autor
Desenvolvido por **[Seu Nome Aqui]**  
Projeto acadêmico para demonstração de **comunicação P2P e Publish/Subscribe em C**.

---

## 📄 Licença
Este projeto é distribuído sob a licença **MIT**.  
Sinta-se à vontade para estudar, modificar e redistribuir o código.
