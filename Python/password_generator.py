#!/usr/bin/python3

import random
import string
import secrets
import argparse
from typing import List, Dict


class PasswordGenerator:
    def __init__(self):
        self.character_sets = {
            'lowercase': string.ascii_lowercase,
            'uppercase': string.ascii_uppercase,
            'digits': string.digits,
            'symbols': string.punctuation
        }
    
    def generate_password(self, length: int = 12, **requirements) -> str:
        """
        Generate a password with specified requirements
        
        Args:
            length: Length of the password
            requirements: Boolean flags for character types
                - lowercase: Include lowercase letters
                - uppercase: Include uppercase letters  
                - digits: Include digits
                - symbols: Include symbols
        
        Returns:
            Generated password string
        """
        # Default requirements if none specified
        if not any(requirements.values()):
            requirements = {
                'lowercase': True,
                'uppercase': True,
                'digits': True,
                'symbols': True
            }
        
        # Build character pool based on requirements
        character_pool = ""
        required_chars = []
        
        for char_type, include in requirements.items():
            if include and char_type in self.character_sets:
                chars = self.character_sets[char_type]
                character_pool += chars
                # Add at least one character from each required type
                required_chars.append(secrets.choice(chars))
        
        if not character_pool:
            raise ValueError("At least one character type must be selected")
        
        # Calculate remaining characters needed
        remaining_length = length - len(required_chars)
        if remaining_length < 0:
            raise ValueError(f"Password length too short for required character types. Minimum: {len(required_chars)}")
        
        # Generate remaining characters
        additional_chars = [secrets.choice(character_pool) for _ in range(remaining_length)]
        
        # Combine and shuffle
        all_chars = required_chars + additional_chars
        secrets.SystemRandom().shuffle(all_chars)
        
        return ''.join(all_chars)
    
    def generate_multiple_passwords(self, count: int = 5, **kwargs) -> List[str]:
        """Generate multiple passwords with the same settings"""
        return [self.generate_password(**kwargs) for _ in range(count)]
    
    def check_password_strength(self, password: str) -> Dict[str, bool]:
        """Check the strength of a password"""
        return {
            'has_lowercase': any(c.islower() for c in password),
            'has_uppercase': any(c.isupper() for c in password),
            'has_digit': any(c.isdigit() for c in password),
            'has_symbol': any(c in string.punctuation for c in password),
            'min_length': len(password) >= 8,
            'good_length': len(password) >= 12
        }


def get_user_preferences():
    """Get password generation preferences from user input"""
    print("=== Password Generator ===")
    
    # Get password length
    while True:
        try:
            length = int(input("Enter password length (default 12): ") or "12")
            if length < 4:
                print("Password length must be at least 4 characters.")
                continue
            break
        except ValueError:
            print("Please enter a valid number.")
    
    # Get character type preferences
    print("\nSelect character types to include:")
    requirements = {
        'lowercase': input("Include lowercase letters? (y/n, default y): ").lower() != 'n',
        'uppercase': input("Include uppercase letters? (y/n, default y): ").lower() != 'n',
        'digits': input("Include digits? (y/n, default y): ").lower() != 'n',
        'symbols': input("Include symbols? (y/n, default y): ").lower() != 'n'
    }
    
    # Get number of passwords to generate
    while True:
        try:
            count = int(input("\nHow many passwords to generate? (default 1): ") or "1")
            if count < 1:
                print("Please enter at least 1.")
                continue
            break
        except ValueError:
            print("Please enter a valid number.")
    
    return length, requirements, count


def display_password_strength(password: str, generator: PasswordGenerator):
    """Display strength analysis for a password"""
    strength = generator.check_password_strength(password)
    
    print(f"\nPassword: {password}")
    print("Strength Analysis:")
    print(f"Length: {len(password)} characters")
    print(f"Lowercase letters: {'Yes' if strength['has_lowercase'] else 'No'}")
    print(f"Uppercase letters: {'Yes' if strength['has_uppercase'] else 'No'}")
    print(f"Digits: {'Yes' if strength['has_digit'] else 'No'}")
    print(f"Symbols: {'Yes' if strength['has_symbol'] else 'No'}")
    
    # Overall strength rating
    criteria_met = sum(strength.values())
    if criteria_met >= 6:
        rating = "Strong"
    elif criteria_met >= 4:
        rating = "Good"
    else:
        rating = "Weak"
    
    print(f"Overall Rating: {rating}")


def main():
    """Main function with command line interface"""
    parser = argparse.ArgumentParser(description='Generate secure passwords')
    parser.add_argument('-l', '--length', type=int, default=12, help='Password length')
    parser.add_argument('-n', '--number', type=int, default=1, help='Number of passwords')
    parser.add_argument('--no-lower', action='store_true', help='Exclude lowercase letters')
    parser.add_argument('--no-upper', action='store_true', help='Exclude uppercase letters')
    parser.add_argument('--no-digits', action='store_true', help='Exclude digits')
    parser.add_argument('--no-symbols', action='store_true', help='Exclude symbols')
    parser.add_argument('--interactive', action='store_true', help='Use interactive mode')
    
    args = parser.parse_args()
    
    generator = PasswordGenerator()
    
    if args.interactive or not any(vars(args).values()):
        # Interactive mode
        length, requirements, count = get_user_preferences()
    else:
        # Command line mode
        length = args.length
        count = args.number
        requirements = {
            'lowercase': not args.no_lower,
            'uppercase': not args.no_upper,
            'digits': not args.no_digits,
            'symbols': not args.no_symbols
        }
    
    try:
        # Generate passwords
        if count == 1:
            password = generator.generate_password(length=length, **requirements)
            display_password_strength(password, generator)
        else:
            passwords = generator.generate_multiple_passwords(count=count, length=length, **requirements)
            print(f"\nGenerated {count} passwords:")
            for i, password in enumerate(passwords, 1):
                print(f"{i:2d}. {password}")
            
            # Show strength for first password as example
            if passwords:
                display_password_strength(passwords[0], generator)
                
    except ValueError as e:
        print(f"Error: {e}")
    except Exception as e:
        print(f"Unexpected error: {e}")


if __name__ == "__main__": 
    main()
