// clipboard_txt.cpp : définit le point d'entrée de l'application.

#include "clipboard_txt.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

int main() {
    // Vérifier si le fichier data.txt existe déjà (A la racine du programme)
    std::ifstream file("data.txt");
    if (!file.is_open()) {
        // Le fichier n'existe pas, créer un nouveau fichier avec le texte "Init data.txt"
        std::ofstream newFile("data.txt");
        if (newFile.is_open()) {
            newFile << "Init data.txt" << std::endl;
            newFile.close();
            std::cout << "Le fichier data.txt a été créé avec succès." << std::endl;
        }
        else {
            std::cerr << "Erreur : Impossible de créer le fichier data.txt." << std::endl;
            return 1;
        }
    }
    else {
        file.close();
    }

    // Ouvrir le fichier contenant la chaîne de caractères (Avec la condition au dessus théoriquement ca passe mais on s'est jamais)
    std::ifstream inputFile("data.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier data.txt." << std::endl;
        return 1;
    }

    // Lire la chaîne de caractères à partir du fichier
    std::string texte;
    std::getline(inputFile, texte);

    // Ouvrir le presse-papiers pour y écrire
    if (OpenClipboard(NULL)) {
        EmptyClipboard(); // Vider le contenu actuel du presse-papiers

        // Allouer de la mémoire globale pour le texte à copier
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, texte.size() + 1);
        if (hMem != NULL) {
            // Obtenir un pointeur vers la mémoire allouée
            char* pData = static_cast<char*>(GlobalLock(hMem));
            if (pData != NULL) {
                // Copier le texte dans la mémoire allouée
                strcpy_s(pData, texte.size() + 1, texte.c_str());
                GlobalUnlock(hMem); // Libérer la mémoire
                // Mettre les données dans le presse-papiers
                SetClipboardData(CF_TEXT, hMem);
                std::cout << "Texte copié dans le presse-papiers avec succès." << std::endl;
            }
            else {
                std::cerr << "Erreur : Impossible de verrouiller la mémoire globale." << std::endl;
            }
        }
        else {
            std::cerr << "Erreur : Impossible d'allouer de la mémoire globale." << std::endl;
        }

        CloseClipboard(); // Fermer le presse-papiers
    }
    else {

        std::cerr << "Erreur : Impossible d'ouvrir le presse-papiers." << std::endl;
    }

    return 0;
}