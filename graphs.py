import matplotlib.pyplot as plt

# Λίστες για τα δεδομένα
pn_values_ant = []
steiners_values_ant = []
obtuses_values_ant = []



categories = {

     "A": [
        ".vscode/challenge_instances_cgshop25/point-set_10_c04b0024.instance.json",
        ".vscode/challenge_instances_cgshop25/point-set_20_0c4009d9.instance.json",
        ".vscode/challenge_instances_cgshop25/point-set_40_1b92b629.instance.json",
        ".vscode/challenge_instances_cgshop25/point-set_60_9fc02edd.instance.json",
        ".vscode/challenge_instances_cgshop25/point-set_80_1675b331.instance.json",
        ".vscode/challenge_instances_cgshop25/point-set_100_0245ce31.instance.json",
        ".vscode/challenge_instances_cgshop25/point-set_150_982c9ab3.instance.json",
        ".vscode/challenge_instances_cgshop25/point-set_250_3c338713.instance.json"
    ],
    "B": [
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_10_46c44a43.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior_10_74050e4d.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_20_1e719235.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_40_84415804.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_60_28a85662.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_100_8d1c2e30.instance.json"
        
    ],
    "C": [
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_250_eb5ab92f.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_20_52abeef5.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_40_5faf6985.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_60_53ad6d23.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_80_f6e462fb.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_100_8ff7a64d.instance.json",

        
    ],

    "D": [
       ".vscode/challenge_instances_cgshop25/ortho_40_df58ce3b.instance.json",
        ".vscode/challenge_instances_cgshop25/ortho_60_5c5796a0.instance.json",
        ".vscode/challenge_instances_cgshop25/ortho_80_06ee55d4.instance.json",
        ".vscode/challenge_instances_cgshop25/ortho_100_bd1e4a14.instance.json",
        ".vscode/challenge_instances_cgshop25/ortho_150_53eb4022.instance.json",
        ".vscode/challenge_instances_cgshop25/ortho_250_3b977f7e.instance.json"
       
    ],
    "E": [
        ".vscode/challenge_instances_cgshop25/simple-polygon_10_297edd18.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon_20_4bd3c2e5.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon_60_0347cd75.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon_80_7b8f6c4c.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon_100_6101abad.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon_150_f24b0f8e.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon_250_6e9d9c26.instance.json",
       
    ],
}

methods=["ls", "sa", "ant"]


# Άνοιγμα του αρχείου και ανάγνωση
for cat , instaces in categories.items():

    for method in methods:
        for inst, i in enumerate(instaces):
            print(i)
        

        with open('.vscode/results/results_{cat}_{i}_{method}.txt', 'r') as file:
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




pn_values_ls= []
steiners_values_ls = []
obtuses_values_ls = []


with open('.vscode/results/results_3_ls.txt', 'r') as file:
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


with open('.vscode/results/results_3_sa.txt', 'r') as file:
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
plt.title('Ροή PN Values για Κάθε Μέθοδο (Γ. Κατηγορία εισόδου)')

# Υποσημειώσεις για τις μεθόδους
plt.legend()

# Προσθήκη grid για καλύτερη οπτικοποίηση
plt.grid(True)

# Εμφάνιση γραφήματος
plt.show()