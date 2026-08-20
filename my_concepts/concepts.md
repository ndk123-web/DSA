# 🧠 Concept Quick Reference & Notes

---

## 1. Custom CLI / Batch Scripts (`System32`)
- Drop `.bat` scripts into `C:\Windows\System32` (or any directory in system `PATH`) to run them globally from any terminal.
- **Examples**:
  - `ndk.bat` → Quick ML model trigger (`LogisticRegression`, `MultinomialNB`).
  - `ndk_java.bat` → Quick execution of utility algorithms (e.g., String permutations `ABC`).

---

## 2. TCP & WebSockets
- **TCP**: Base-level transport protocol (stream-oriented, duplex).
- **WebSocket**: Full-duplex persistent connection over a single TCP socket (ideal for real-time messaging).
- **Core Pattern**:
  - Event-driven (`emit` and `on`).
  - Server maintains active connection state in a Map/Dictionary (`userId -> socketId`).

---

## 3. Jupyter / Python Notebook Environments
| Environment | Kernel Management | Host / Execution |
| :--- | :--- | :--- |
| **Google Colab** | Managed by Google | Cloud browser-based; managed compute/backend |
| **VS Code (`.ipynb`)** | Local `ipykernel` | Local IDE with Jupyter extension |
| **JupyterLab** | Local `ipykernel` | Local web server interface executing locally |

---

## 4. Python Module Execution (`-m`)
- Running `python file.py` adds only that file's directory to `sys.path`.
- **Best Practice**: Always execute as a module from the project root:
  ```bash
  python -m package_name.file_name
  ```
  *(Prevents `ModuleNotFoundError` and resolves absolute imports cleanly)*.

---

## 5. GCP Authentication Hierarchy
| Auth Type | Meaning / Purpose |
| :--- | :--- |
| **API Key** | *"This is my application / project"* (identifies project, basic quota/billing) |
| **OAuth 2.0** | *"User allowed me to act on their behalf"* (delegated user permissions) |
| **Service Account** | *"I am the server / backend service"* (machine-to-machine auth via private keys) |

---

## 6. Threads vs Processes
- **Process**: Independent memory space, heavier to spawn.
- **Thread**: Shares memory space within a process, lightweight.
- **Execution**: Runs concurrently on CPU cores or via time-slicing (multitasking).

---

## 7. Git Cheatsheet & Recovery Scenarios

### Essential Commands
- `git add .` → Working Directory ➔ Staging Area
- `git commit -m "msg"` → Staging Area ➔ Local Repository
- `git push origin <branch>` → Local Repository ➔ Remote Repository
- `git fetch origin <branch>` → Fetch remote commits without merging
- `git pull origin <branch>` → Fetch + Merge into current local branch
- `git switch <branch>` / `git checkout -b <new-branch>` → Switch / Create & switch branch
- `git rebase <target-branch>` → Replay current commits on top of target branch
- `git stash` / `git stash pop` / `git stash apply` → Temporarily stash uncommitted work

### Common Recovery Scenarios
```bash
# 1. Unstage accidentally added files (Staging -> Working directory)
git restore --staged <file_path>

# 2. Undo last commit but keep changes staged & in working dir
git reset --soft HEAD~1

# 3. Reset types comparison:
# --soft  : removes commit, keeps files staged & in working dir
# --mixed : removes commit & un-stages files, keeps files in working dir (default)
# --hard  : discards commit, staging, AND all uncommitted file changes (destructive)
```

---

## 8. JWT (JSON Web Token)

### Structure: `Header.Payload.Signature`
- **Header**: Algorithm and token type (Base64 URL encoded).
- **Payload**: Claims and data (Base64 URL encoded, **not encrypted** - readable by anyone).
- **Signature**: Ensures data integrity and verifies the issuer.

---

### Symmetric vs Asymmetric Signing

#### A. Symmetric JWT (`HS256`)
- **Single Secret Key** used for both **Signing** and **Verification**.
- Best when the same backend service issues and verifies the token.
- *Use case*: Monolithic backend, internal session tokens.

#### B. Asymmetric JWT (`RS256`)
- **Two Keys**:
  - `Private Key` (Secret): Used **only to sign** the token.
  - `Public Key` (Publicly shared): Used **only to verify** the signature.
- *Use case*: Auth providers (Firebase, Google Auth, Auth0, Microservices).

#### Firebase / Google Auth Flow
```
User Signs In (Google / Firebase)
             │
             ▼
Google signs ID Token with its Private Key
             │
             ▼
Frontend receives ID Token and sends it to Backend API
             │
             ▼
Backend fetches Google's Public Certificate / Key
             │
             ▼
Backend verifies (Signature, aud, iss, exp) ──► Authenticated!
```

---

## 9. System & Application Architecture

### I. System-Level Patterns (Macro Architecture)
- **Monolith**: Single unified process/deployment for the entire domain.
- **Modular Monolith**: Single process with strict logical domain boundaries/modules (Users, Billing, etc.).
- **Microservices**: Independently deployable services with independent databases communicating via HTTP/gRPC.
- **Microkernel (Plugin Architecture)**: Core system provides minimal base workflow; capabilities extend via independent plugins (e.g., VS Code extensions, Jenkins).
- **Other Models**: N-Tier, Service-Oriented (SOA), Serverless, Distributed, Peer-to-Peer (P2P).

---

### II. Application-Level Patterns (Codebase Architecture)

#### 1. Layered (Traditional)
```
Entry / Routes ──► Controllers ──► Services ──► Repositories ──► Database
```
*(Downward dependency - can lead to tight coupling with DB/infrastructure)*.

---

#### 2. Onion Architecture (Clean Domain-Driven Design)
Dependencies point inward. Core business logic is isolated and has zero dependencies on databases or UI.

```
my_backend/
├── domain/                      # Core business logic (Pure, no external dependencies)
│   ├── entities/                # e.g., Order.js
│   └── interfaces/              # Repository contracts (e.g., OrderRepository.js)
│
├── application/                 # Use cases / Orchestration logic
│   └── usecases/                # e.g., CreateOrder.js (calls interface contracts)
│
├── infrastructure/              # Concrete implementations of interfaces
│   ├── postgres/                # e.g., PostgresOrderRepository.js
│   └── mongo/                   # e.g., MongoOrderRepository.js
│
├── presentation/                # Adapters for HTTP / UI
│   └── controllers/             # e.g., OrderController.js (invokes use cases)
│
├── routes/                      # Route definitions (e.g., orderRoutes.js)
└── app.js                       # Dependency injection & server bootstrap
```

---

#### 3. Hexagonal Architecture (Ports & Adapters)
- Core domain logic lives inside a hexagon.
- Communicates with external worlds (DB, UI, message brokers) via **Ports** (interfaces) and **Adapters** (concrete implementations).
