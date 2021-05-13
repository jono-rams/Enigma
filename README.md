# Enigma
Enigma machine implementation in C++

This project is a **Work in Progress** the current progress of features can be found [here](https://github.com/c1ph3r-dev/Enigma/projects/1).
The roadmap has recently been created and will be updated over the next few days and weeks.

## ALPHA 1 CHANGELOG
* Base Core class has been created.
  * Pair module implemented in Core.
    * Users can generate a default pair module that emulates the Atbash cipher.
    * Users can generate their own custom Pairs
      * A check has been implemented to make sure it's only valid characters.
      * A check has been implemented to make sure no duplicate characters are in any of the pairs.
* Users can encrypt a string of valid characters using pairs module.
  * A check has been implemented to ensure it's only valid characters.

## ALPHA 2 CHANGELOG
* Rotor modules implemented in Core.
  * 5 Rotors created and can be edited by user.
  * User can set any three Rotors in any order.
* Encryption fully implemented.

## BETA 1 CHANGELOG
* Encryption now takes a string instead of character.
  * Can output a string or write to a string reference.
* Improved Error Handling.
* Better memory management.
  * Most is done manually in the code by the programmer.

## BETA 2 CHANGELOG
* IN PROGRESS
