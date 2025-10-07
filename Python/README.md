# Password Generator

A secure and customizable password generator written in Python. This tool allows you to create strong passwords with various character types and provides strength analysis for generated passwords.

## Features

- 🔒 **Cryptographically Secure**: Uses Python's `secrets` module for secure random generation
- ⚙️ **Customizable**: Choose password length and character types
- 📊 **Strength Analysis**: Get detailed feedback on password strength
- 🔢 **Batch Generation**: Generate multiple passwords at once
- 🖥️ **Dual Interface**: Both interactive and command-line modes
- 🎯 **Smart Defaults**: Ensures at least one character from each selected type

## Installation

### Prerequisites
- Python 3.6 or higher

### Setup
1. **Clone or download** the script to your local machine
2. **Make executable** (optional):
   ```bash
   chmod +x password_generator.py
   ```

## Usage

### Interactive Mode (Recommended for beginners)

Run the script without arguments to enter interactive mode:

```bash
python3 password_generator.py
```

or if executable:

```bash
./password_generator.py
```

You'll be prompted for:
- Password length (default: 12)
- Character types to include (lowercase, uppercase, digits, symbols)
- Number of passwords to generate (default: 1)

### Command Line Mode

For quick password generation or scripting:

#### Basic Usage
```bash
# Generate one strong password with default settings (12 characters, all types)
python3 password_generator.py

# Generate a 16-character password
python3 password_generator.py -l 16

# Generate 5 passwords
python3 password_generator.py -n 5
```

#### Advanced Options
```bash
# Generate password without symbols
python3 password_generator.py --no-symbols

# Generate numeric PIN (6 digits)
python3 password_generator.py -l 6 --no-lower --no-upper --no-symbols

# Generate letters-only password
python3 password_generator.py --no-digits --no-symbols

# Force interactive mode
python3 password_generator.py --interactive
```

### Command Line Arguments

| Argument | Short | Description | Default |
|----------|-------|-------------|---------|
| `--length` | `-l` | Password length | 12 |
| `--number` | `-n` | Number of passwords to generate | 1 |
| `--no-lower` | | Exclude lowercase letters | Included |
| `--no-upper` | | Exclude uppercase letters | Included |
| `--no-digits` | | Exclude digits | Included |
| `--no-symbols` | | Exclude symbols | Included |
| `--interactive` | | Force interactive mode | Auto-detect |

## Examples

### Strong Password
```bash
python3 password_generator.py -l 16
# Example output: Xk8#pL$2*mQ9!vR@
```

### Multiple Passwords
```bash
python3 password_generator.py -n 3 -l 10
```
Output:
```
Generated 3 passwords:
 1. aB3$fG8!kL
 2. pQ9@mN2#rT
 3. xY7!vW4$zU
```

### Application-Specific Passwords
```bash
# API Key style (letters and digits only)
python3 password_generator.py -l 32 --no-symbols

# PIN code
python3 password_generator.py -l 6 --no-lower --no-upper --no-symbols

# Memorable password (letters only)
python3 password_generator.py -l 14 --no-digits --no-symbols
```

## Password Strength Ratings

The generator provides strength analysis based on:
- **Length**: Minimum 8 characters, good at 12+
- **Character diversity**: Lowercase, uppercase, digits, symbols
- **Overall rating**:
  - **Strong**: Meets 6+ criteria
  - **Good**: Meets 4-5 criteria  
  - **Weak**: Meets 3 or fewer criteria

## Security Notes

- ✅ Uses cryptographically secure random number generation
- ✅ Ensures minimum character requirements are met
- ✅ Properly shuffles final passwords
- ✅ No passwords are stored or transmitted
- ⚠️ Generated passwords are displayed in terminal - clear your history if needed

## Troubleshooting

### Common Issues

**"Password length too short" error**
- Solution: Increase password length or reduce character type requirements

**No characters selected**
- Solution: Enable at least one character type (lowercase, uppercase, digits, or symbols)

**Permission denied**
- Solution: Make script executable with `chmod +x password_generator.py`

### Requirements
- Python 3.6+ (for `secrets` module and type hints)
