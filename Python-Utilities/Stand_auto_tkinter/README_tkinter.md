# PI06 New Used Cars

Aplicação desktop de gestão de uma loja de carros usados, desenvolvida em Python com interface gráfica Tkinter.

## Descrição

A aplicação simula o sistema de uma loja de carros usados com dois tipos de utilizador: **administrador** e **cliente**. Cada perfil tem acesso a funcionalidades distintas após autenticação.

- O **administrador** gere o stock — adiciona, consulta e remove viaturas.
- O **cliente** navega no inventário, filtra carros e pode comprar.

## Estrutura do Projeto

```
pi06-new-used-cars/
├── main.py                 # Aplicação principal
├── user_database.json      # Base de dados de utilizadores e produtos
└── README.md
```

## Funcionalidades

### Autenticação
- Login e registo de utilizadores
- Dois perfis: administrador e cliente
- Dados persistidos em ficheiro JSON

### Painel de Administrador
- Inserção de novas viaturas com campos: Marca, Modelo, Tração, Kms, Ano, Matrícula e Preço
- Listagem e filtragem do inventário
- Remoção de viaturas por matrícula

### Loja (Cliente)
- Visualização do inventário disponível
- Pesquisa e filtragem em tempo real
- Compra de viaturas (remove do stock)

## Instalação e Execução

### Pré-requisitos

- Python 3.8+
- Tkinter (incluído na instalação padrão do Python)

### Executar

```bash
python main.py
```

## Formato da Base de Dados

O ficheiro `user_database.json` segue a seguinte estrutura:

```json
{
  "USERBASE": [
    {
      "username": "admin",
      "password": "admin123",
      "admin": true
    }
  ],
  "Products": [
    {
      "Brand": "Toyota",
      "Model": "Corolla",
      "Traction": "FWD",
      "Kms": "50000",
      "Year": "2019",
      "License Plate": "AA-00-BB",
      "Price": "12000"
    }
  ]
}
```

## Limitações Conhecidas

- As passwords são armazenadas em texto simples no JSON. Numa versão futura seria aplicado hashing com salt (como implementado no projeto `basic_login`).

## Tecnologias Utilizadas

- **Tkinter** — interface gráfica desktop
- **JSON** — persistência de dados
- **pathlib** — gestão de caminhos de ficheiros
