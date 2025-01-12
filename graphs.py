import matplotlib.pyplot as plt

# Λίστες για τα δεδομένα
pn_values_ant = []
steiners_values_ant = []
obtuses_values_ant = []

# Άνοιγμα του αρχείου και ανάγνωση
with open('.vscode/results_4_ant.txt', 'r') as file:
    lines = file.readlines()

    for line in lines:
        if line.startswith("pn:"):  # Αν η γραμμή ξεκινάει με 'pn:', τότε έχουμε δεδομένα
            # Διαχωρισμός των τιμών της γραμμής
            parts = line.split()
            pn = float(parts[0].split(":")[1])  # Παίρνουμε την τιμή του pn
            obtuses = int(parts[1].split(":")[1])  # Παίρνουμε την τιμή των obtuses
            steiners = int(parts[2].split(":")[1])  # Παίρνουμε την τιμή των steiners
            
            # Αποθήκευση των τιμών στις αντίστοιχες λίστες
            pn_values_ant.append(pn)
            steiners_values_ant.append(steiners)
            obtuses_values_ant.append(obtuses)

# Εκτύπωση των τιμών για έλεγχο
print('Values of ant resultss:')
print(pn_values_ant)
print(steiners_values_ant)
print(obtuses_values_ant)


pn_values_ls= []
steiners_values_ls = []
obtuses_values_ls = []


with open('.vscode/results_4_ls.txt', 'r') as file:
    lines = file.readlines()

    for line in lines:
        if line.startswith("pn:"):  # Αν η γραμμή ξεκινάει με 'pn:', τότε έχουμε δεδομένα
            # Διαχωρισμός των τιμών της γραμμής
            parts = line.split()
            pn = float(parts[0].split(":")[1])  # Παίρνουμε την τιμή του pn
            obtuses = int(parts[1].split(":")[1])  # Παίρνουμε την τιμή των obtuses
            steiners = int(parts[2].split(":")[1])  # Παίρνουμε την τιμή των steiners
            
            
            # Αποθήκευση των τιμών στις αντίστοιχες λίστες
            pn_values_ls.append(pn)
            steiners_values_ls.append(steiners)
            obtuses_values_ls.append(obtuses)

pn_values_sa= []
steiners_values_sa = []
obtuses_values_sa = []


with open('.vscode/results_4_sa.txt', 'r') as file:
    lines = file.readlines()

    for line in lines:
        if line.startswith("pn:"):  # Αν η γραμμή ξεκινάει με 'pn:', τότε έχουμε δεδομένα
            # Διαχωρισμός των τιμών της γραμμής
            parts = line.split()
            pn = float(parts[0].split(":")[1])  # Παίρνουμε την τιμή του pn
            obtuses = int(parts[1].split(":")[1])  # Παίρνουμε την τιμή των obtuses
            steiners = int(parts[2].split(":")[1])  # Παίρνουμε την τιμή των steiners
            
            # Αποθήκευση των τιμών στις αντίστοιχες λίστες
            pn_values_sa.append(pn)
            steiners_values_sa.append(steiners)
            obtuses_values_sa.append(obtuses)






# Σχεδιάζουμε το γράφημα για τις 3 μεθόδους (ls, ant, sa)
plt.figure(figsize=(10, 6))

# Μεθόδος LS (ls)
plt.plot(steiners_values_ls, pn_values_ls, marker='o', label='LS Method (pn)', color='blue')

# Μεθόδος ANT (ant)
plt.plot(steiners_values_ant, pn_values_ant, marker='o', label='ANT Method (pn)', color='red')

# Μεθόδος SA (sa)
plt.plot(steiners_values_sa, pn_values_sa, marker='o', label='SA Method (pn)', color='green')

# Προσθήκη αξόνων και τίτλων
plt.xlabel('Steiner Points (Steiners)')
plt.ylabel('PN Values (pn)')

# Τίτλος γραφήματος
plt.title('Ροή PN Values για Κάθε Μέθοδο (Ε. Κατηγορία εισόδου)')

# Υποσημειώσεις για τις μεθόδους
plt.legend()

# Προσθήκη grid για καλύτερη οπτικοποίηση
plt.grid(True)

# Εμφάνιση γραφήματος
plt.show()