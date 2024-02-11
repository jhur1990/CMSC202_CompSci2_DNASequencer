
#include "Sequencer.h"

// Sequencer
// Constructor that populates the data file
Sequencer::Sequencer(string fileName) {
    m_fileName = fileName;
}

// ~Sequencer
// Destructor that clears and deallocates the vectors of DNA or mRNA strands
Sequencer::~Sequencer() {
    cout << "Deleting DNA Strands" << endl;
    
    // Iterates through the m_DNA vector and deletes each dynamically allocated objects
    for (unsigned int i = 0; i < m_DNA.size(); i++) {
        delete m_DNA[i];
    }
    
    cout << "Deleting mRNA Strands" << endl;

    // Iterates through the m_mRNA vector and deletes each dynamically allocated objects
    for (unsigned int i = 0; i < m_mRNA.size(); i++) {
        delete m_mRNA[i];
    }
}

// StartSequencing
// Calls ReadFile and continually calls mainmenu until the user exits
void Sequencer::StartSequencing() {
    ReadFile();
    int menu_choice = 0;
    
    // Keeps running the main menu
    while (menu_choice == 0) {
        menu_choice = MainMenu();
    }
}

// DisplayStrands
// Displays saved DNA and mRNA strands from the vectors
void Sequencer::DisplayStrands() {
    int count = 1; // Initializes the start number of DNA or mRNA lists
    
    cout << endl;
    
    // Iterates and displays the list of DNA strands
    for (unsigned int i = 0; i < m_DNA.size(); i++) {
        cout << "DNA " << count << endl;
        cout << "***" << m_DNA[i] -> GetName() << "***" << endl;
        cout << *m_DNA[i] << endl;
        count++;
    }
    count = 1;
    
    // Iterates and displays the list of mRNA strands
    for (unsigned int i = 0; i < m_mRNA.size(); i++) {
        cout << "mRNA " << count << endl;
        cout << "***" << m_mRNA[i] -> GetName() << "***" << endl;
        cout << *m_mRNA[i] << endl;
        count++;
    }
}

// ReadFile
// Opens a data file and loads DNA strands
void Sequencer::ReadFile() {
    
    // Opens the input file
    ifstream infile(m_fileName);
    
    // Checks if the file opened successfully
    if (!infile) {
        cout << "Unable to open file: " << m_fileName << endl;
        
    } else {
        string line, name, seq; // Variables to store the line, name, and sequence from the file
        
        // Reads the file line by line, using ',' as the delimiter
        while (getline(infile, line, ',')) {
            // Sets the name to the current line and reads the next line
            name = line;
            getline(infile, seq);
            
            // Creates a new strand object with the name
            Strand *newStrand = new Strand(name);
            
            // Iterates through the sequence string and adds each character to the strand
            for (unsigned int i = 0; i < seq.length(); i++) {
                if (seq[i] != ',' && seq[i] != '\n') {
                    newStrand -> InsertEnd(seq[i]);
                }
            }
            
            // Adds the new strand to the m_DNA vector
            m_DNA.push_back(newStrand);
        }
        
        // Output messages indicating that the file was opened and the number of strands loaded
        cout << "Opened file" << endl;
        cout << m_DNA.size() << " strands loaded." << endl;
    }
    infile.close();
}

// MainMenu
// Displays the main menu of the program and processes the user's choice
int Sequencer::MainMenu() {
    int choice; // Variable to store the user's choice
    
    // Displays the main menu options
    cout << endl;
    cout << "What would you like to do?:" << endl;
    cout << "1. Display Strands" << endl;
    cout << "2. Reverse Strand" << endl;
    cout << "3. Transcribe DNA to mRNA" << endl;
    cout << "4. Translate mRNA to Amino Acids" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    
    // Validates the user's input and ensure it is between 1 and 5
    while (choice < 1 || choice > 5) {
        cout << endl;
        cout << "Invalid Input. Please enter a number between 1 and 5." << endl;
        cout << "What would you like to do?:" << endl;
        cout << "1. Display Strands" << endl;
        cout << "2. Reverse Strand" << endl;
        cout << "3. Transcribe DNA to mRNA" << endl;
        cout << "4. Translate mRNA to Amino Acids" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
    }
    
    // Functions
    if (choice >= 1 && choice <= 4) {
        switch (choice) {
            case 1:
                
                // Displays the strands
                DisplayStrands();
                break;
                
            case 2:
                
                // Reverses a strand
                ReverseSequence();
                break;
                
            case 3:
                
                // Transcribe DNA to mRNA
                Transcribe();
                break;
                
            case 4:
                
                // Translate mRNA to Amino Acids
                Translate();
                break;
        }
        return 0;
        
    } else {
        // Option 5: Exit
        cout << endl;
        cout << "Exiting program" << endl;
        return 5;
    }
}

// ReverseSequence
// Reverses the sequence of the selected DNA or mRNA strand
void Sequencer::ReverseSequence() {
    int choice; // Variable to store the user's choice
    
    cout << endl;
    do{
        // Prompts the user to choose which type of strand to reverse
        cout << "Which type of strand to reverse?" << endl;
        cout << "1. DNA" << endl;
        cout << "2. mRNA" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        // If the user chooses to reverse a DNA strand
        if (choice == 1) {
            
            // Calls the ChooseDNA function to get the index of the selected DNA strand
            int index = ChooseDNA();
            
            // If a valid index is returned, reverse the DNA strand sequence
            if (index != -1) {
                m_DNA[index] -> ReverseSequence();
                cout << "Done reversing DNA " << index + 1 << "'s strand" << endl;
            }
            
        // If the user chooses to reverse an mRNA strand sequence
        } else if (choice == 2) {
            
            // Calls the ChooseMRNA function to get the index of the selected mRNA strand
            int index = ChooseMRNA();
            
            // If a valid index is returned, reverse the mRNA strand sequence
            if (index != -1) {
                m_mRNA[index] -> ReverseSequence();
                cout << "Done reversing mRNA " << index + 1 << "'s strand" << endl;
            } else {
                cout << "No mRNA to reverse; transcribe first" << endl;
            }
            
        } else {
            cout << endl;
            cout << "Invalid choice. Please try again." << endl;
        }
        
    // Repeats until the user enteres a valid choice; only 1 and 2
    } while (choice < 1 || choice > 2);
}

// ChooseDNA
// Prompts the user to select a DNA strand returns its index
int Sequencer::ChooseDNA() {
    unsigned int choice; // Variable to store the user's choice
    
    // Checks if there are any DNA strands available
    if (m_DNA.size() < 1) {
        cout << "No DNA is available" << endl;
        return -1;
        
    } else {
        
        // Checks if there is only one DNA strand
        if (m_DNA.size() == 1){
            return 0;
            
        } else {
            cout << endl;
            cout << "Which strand to work with?" << endl;
            cout << "Choose a DNA strand(1 - " << m_DNA.size() << "):" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            
            // Validates the user's input and ensure it is within the range of available DNA strands
            while (choice < 1 || choice > m_DNA.size()) {
                cout << endl;
                cout << "Invalid choice. Please enter between 1 - " << m_DNA.size() << "." << endl;
                cout << "Which strand to work with?" << endl;
                cout << "Choose a DNA strand(1 - " << m_DNA.size() << "):" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
            }
            
            return choice - 1;
        }
    }
}

// ChooseMRNA
// Prompts the user to select an mRNA strand returns its index
int Sequencer::ChooseMRNA() {
    unsigned int choice; // Variable to store the user's choice
    
    // Checks if there are any mRNA strands available
    if (m_mRNA.size() < 1) {
        return -1;
        
    } else {
        
        // Checks if there is only one mRNA strand
        if (m_mRNA.size() == 1){
            return 0;
            
        } else {
            cout << endl;
            cout << "Which strand to work with?" << endl;
            cout << "Choose a mRNA strand(1 - " << m_mRNA.size() << "):" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            
            // Validates the user's input and ensure it is within the range of available mRNA strands
            while (choice < 1 || choice > m_mRNA.size()) {
                cout << endl;
                cout << "Invalid choice. Please enter between 1 - " << m_mRNA.size() << endl;
                cout << "Which strand to work with?" << endl;
                cout << "Choose a mRNA strand(1 - " << m_mRNA.size() << "):" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
            }
            
            return choice - 1;
        }
    }
}

// Transcribe
// Transcribes all DNA strands into corresponding mRNA strands
void Sequencer::Transcribe() {
    
    // Iterates through all DNA strands
    for (unsigned int i = 0; i < m_DNA.size(); i++) {
        // Creates a new mRNA strand with the same name as the DNA strand
        Strand* newStrand = new Strand(m_DNA[i] -> GetName());
        
        // Iterates through each nucleotide in the DNA strand
        for (int j = 0; j < m_DNA[i] -> GetSize(); j++) {
            // Gets the DNA nucelotide
            char nucleotide = m_DNA[i] -> GetData(j);
            char mRNA_nucleotide = ' ';
            
            // Determines the correspondng mRNA nucleotide
            switch (nucleotide) {
                case 'A':
                    mRNA_nucleotide = 'U';
                    break;
                case 'T':
                    mRNA_nucleotide = 'A';
                    break;
                case 'C':
                    mRNA_nucleotide = 'G';
                    break;
                case 'G':
                    mRNA_nucleotide = 'C';
                    break;
            }
            
            // Inserts the mRNA nucleotides into the new mRNA strand
            newStrand -> InsertEnd(mRNA_nucleotide);
        }
        
        // Adds the new mRNA strand to the list of mRNA strands
        m_mRNA.push_back(newStrand);
    }
    cout << m_DNA.size() << " strands of DNA successfully transcribed into new mRNA strands" << endl;
}

// Translate
// Translates the selected mRNA strand into a sequence of amino acids
void Sequencer::Translate() {
    const int TRINUCLEOTIDE_LENGTH = 3; // Length of trinucelotides
    
    // Calls the ChooseMRNA to get the index of the selected mRNA strand
    int index = ChooseMRNA();
    
    // Checks if a valid mRNA strand index is returned
    if (index != -1) {
        // Get the selected mRNA strand
        Strand* strand = m_mRNA[index];
        cout << endl;
        cout << strand -> GetName() << endl;
        
        // Iterates through the mRNA strand in steps of 3 nucleotides (codon)
        for (int i = 0; i < strand -> GetSize(); i += TRINUCLEOTIDE_LENGTH) {
            
            // Checks if there are enough nucleotides left for a complete codon and creates codons
            if (i + 2 < strand -> GetSize()) {
                string codon = "";
                codon += strand -> GetData(i);
                codon += strand -> GetData(i + 1);
                codon += strand -> GetData(i + 2);
                cout << strand -> GetData(i) << strand -> GetData(i + 1) << strand -> GetData(i + 2) << " -> " << Convert(codon) << " " << endl;
            }
        }
        
    } else {
        cout << "No mRNA to translate; transcribe first" << endl;
    }
}

// Convert
// Converts a given trinucleotide (codon) into its corresponding amino acid
string Sequencer::Convert(const string trinucleotide) {
    // Checks the input trinucleotide and returns the corresponding amino acid
    if((trinucleotide=="AUU")||(trinucleotide=="AUC")||(trinucleotide=="AUA"))
        return ("Isoleucine");
    else if((trinucleotide=="CUU")||(trinucleotide=="CUC")||(trinucleotide=="CUA")||
      (trinucleotide=="CUG")|| (trinucleotide=="UUA")||(trinucleotide=="UUG"))
        return ("Leucine");
    else if((trinucleotide=="GUU")||(trinucleotide=="GUC")||
      (trinucleotide=="GUA")||(trinucleotide=="GUG"))
        return ("Valine");
    else if((trinucleotide=="UUU")||(trinucleotide=="UUC"))
        return ("Phenylalanine");
    else if((trinucleotide=="AUG"))
        return ("Methionine (START)");
    else if((trinucleotide=="UGU")||(trinucleotide=="UGC"))
        return ("Cysteine");
    else if((trinucleotide=="GCU")||(trinucleotide=="GCC")||
      (trinucleotide=="GCA")||(trinucleotide=="GCG"))
        return ("Alanine");
    else if((trinucleotide=="GGU")||(trinucleotide=="GGC")||
      (trinucleotide=="GGA")||(trinucleotide=="GGG"))
        return ("Glycine");
    else if((trinucleotide=="CCU")||(trinucleotide=="CCC")||
      (trinucleotide=="CCA")||(trinucleotide=="CCG"))
        return ("Proline");
    else if((trinucleotide=="ACU")||(trinucleotide=="ACC")||
      (trinucleotide=="ACA")||(trinucleotide=="ACG"))
        return ("Threonine");
    else if((trinucleotide=="UCU")||(trinucleotide=="UCC")||
      (trinucleotide=="UCA")||(trinucleotide=="UCG")||
      (trinucleotide=="AGU")||(trinucleotide=="AGC"))
        return ("Serine");
    else if((trinucleotide=="UAU")||(trinucleotide=="UAC"))
        return ("Tyrosine");
    else if((trinucleotide=="UGG"))
        return ("Tryptophan");
    else if((trinucleotide=="CAA")||(trinucleotide=="CAG"))
        return ("Glutamine");
    else if((trinucleotide=="AAU")||(trinucleotide=="AAC"))
        return ("Asparagine");
    else if((trinucleotide=="CAU")||(trinucleotide=="CAC"))
        return ("Histidine");
    else if((trinucleotide=="GAA")||(trinucleotide=="GAG"))
        return ("Glutamic acid");
    else if((trinucleotide=="GAU")||(trinucleotide=="GAC"))
        return ("Aspartic acid");
    else if((trinucleotide=="AAA")||(trinucleotide=="AAG"))
        return ("Lysine");
    else if((trinucleotide=="CGU")||(trinucleotide=="CGC")||(trinucleotide=="CGA")||
      (trinucleotide=="CGG")||(trinucleotide=="AGA")||(trinucleotide=="AGG"))
        return ("Arginine");
    else if((trinucleotide=="UAA")||(trinucleotide=="UAG")||(trinucleotide=="UGA"))
        return ("Stop");
    else
        cout << "returning unknown" << endl;
    return ("Unknown");
}
