import matplotlib.pyplot as plt
import re


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
avg_avg={}

def avg_pn():
    # Άνοιγμα του αρχείου και ανάγνωση
    for cat , instaces in categories.items():
        sum_avg_pn = {method: 0 for method in methods}
        count = {method: 0 for method in methods}
        for method in methods:
            for i, inst in enumerate(instaces):
                #print(f'i: {i+1}, method: {method}, category: {cat}')
                
                with open(f'.vscode/results/results_{cat}_{i+1}_{method}.txt', 'r') as file:
                    lines = file.readlines()

                    for line in lines:
                        if line.startswith("Μέσος ρυθμός σύγκλισης:"):  # Αν η γραμμή ξεκινάει με 'pn:', τότε έχουμε δεδομένα
                            # Διαχωρισμός των τιμών της γραμμής
                            parts = line.split()
                            avg_pn = float(line.split(":")[1])   # Παίρνουμε την τιμή του pn
                            sum_avg_pn[method] += avg_pn
                            count[method] += 1
        avg_avg[cat] = {method: (sum_avg_pn[method] / count[method] if count[method] > 0 else 0) for method in methods}
    ##  print(cat)
    #  print(avg_avg[cat])



    for cat, method_averages in avg_avg.items():
        plt.figure(figsize=(8, 6))
        methods_list = list(method_averages.keys())
        averages = list(method_averages.values())
        
        # Δημιουργία μπάρας
        plt.bar(methods_list, averages, color=['blue', 'green', 'red'], width=0.5)
        
        # Προσαρμογή του y-άξονα για αρνητικές τιμές
        y_min = min(averages) * 1.2 if min(averages) < 0 else 0
        y_max = max(averages) * 1.2 if max(averages) > 0 else 0
        plt.ylim(y_min, y_max)
        
        # Προσαρμογές στο διάγραμμα
        plt.title(f"Μέσος ρυθμός σύγκλισης για την κατηγορία: {cat}")
        plt.xlabel("Μέθοδος")
        plt.ylabel("Μέσος ρυθμός σύγκλισης")
        plt.xticks(rotation=45)
        plt.grid(axis="y", linestyle="--", alpha=0.7)
        
        # Εμφάνιση του διαγράμματος
        plt.tight_layout()
        plt.show()

def energy_finding():
    missing_avg_files = {}  # Λεξικό για αποθήκευση αποτελεσμάτων

    # Έλεγχος για κάθε κατηγορία, instance, και μέθοδο
    for cat, instances in categories.items():
        for i, inst in enumerate(instances):
            for method in methods:
                file_path = f'.vscode/results/results_{cat}_{i+1}_{method}.txt'
                with open(file_path, 'r') as file:
                    lines = file.readlines()
                            
                            # Έλεγχος αν υπάρχει "Μέσος ρυθμός σύγκλισης"
                    #has_avg = any("Μέσος ρυθμός σύγκλισης:" in line for line in lines)
                    has_energy = any("Ενέργεια τριγωνοποίσης που δεν συγκλίνει:" in line for line in lines)
                    has_avg = any("Μέσος ρυθμός σύγκλισης:" in line for line in lines)

                            
                        # Αν δεν έχει "Μέσος ρυθμός σύγκλισης" αλλά έχει "Ενέργεια"
                    if not has_avg and has_energy:
                        if cat not in missing_avg_files:
                            missing_avg_files[cat] = []
                        missing_avg_files[cat].append((i+1, method))
# Αναζήτηση για κάθε κατηγορία αν υπάρχει instance με όλες τις μεθόδους στο missing_avg_files
    instances_with_all_missing_methods = {}

    # Έλεγχος για κάθε κατηγορία
    for cat, files in missing_avg_files.items():
        # Δημιουργία ενός λεξικού για να παρακολουθούμε ποια instances έχουν όλες τις μεθόδους
        instance_methods = {}

        # Κωδικοποίηση των μεθόδων σε λίστα
        for inst, meth in files:
            if inst not in instance_methods:
                instance_methods[inst] = set()
            instance_methods[inst].add(meth)

        # Έλεγχος για κάθε instance αν έχει και τις τρεις μεθόδους
        for inst, meth in instance_methods.items():
            if len(meth) == 3:  # Αν έχει και τις τρεις μεθόδους
                if cat not in instances_with_all_missing_methods:
                    instances_with_all_missing_methods[cat] = []
                instances_with_all_missing_methods[cat].append(inst)




    if missing_avg_files:
        print("Αρχεία που περιέχουν 'Ενέργεια' αλλά όχι 'Μέσος ρυθμός σύγκλισης':")
        for cat, files in missing_avg_files.items():
            print(f"\nΚατηγορία: {cat}")
            for inst, method in files:
                print(f"  - Instance: {inst}, Μέθοδος: {method}")
    else:
        print("Όλα τα αρχεία έχουν 'Μέσος ρυθμός σύγκλισης'.")
        
    # Εμφάνιση των αποτελεσμάτων
    if instances_with_all_missing_methods:
        print("Instances που δεν συγκλίνουν με καμία από τις 3 μεθόδους")
        for cat, instances in instances_with_all_missing_methods.items():
            print(f"\nΚατηγορία: {cat}")
            for inst in instances:
                print(f"  - Instance: {inst}")
    else:
        print("Δεν υπάρχουν instances που δεν συγκλίνουν σε καμία από τις 3 μεθόδους.")





def percentage_graph():
    avg_per={}
    percentage_pattern = r'(-?\d+(\.\d+)?)%'
    for cat , instaces in categories.items():
        sum_percent = {method: 0 for method in methods}
        count = {method: 0 for method in methods}
        for method in methods:
            for i, inst in enumerate(instaces):
                #print(f'i: {i+1}, method: {method}, category: {cat}')
                
                with open(f'.vscode/results/results_{cat}_{i+1}_{method}.txt', 'r') as file:
                    lines = file.readlines()

                    for line in lines:
                        match = re.search(percentage_pattern, line)
                        
                        if match:  # Αν βρέθηκε ποσοστό
                            # Λήψη της πρώτης ομάδας από την αντιστοιχία (την τιμή του ποσοστού)
                            per = float(match.group(1))
                print(f'{cat}_{i}_{method} -> {per}')
                sum_percent[method] += per
                count[method] += 1
        avg_per[cat] = {method: (sum_percent[method] / count[method] if count[method] > 0 else 0) for method in methods}
        print(cat)
        print(avg_per[cat])



    for cat, method_averages in avg_per.items():
        plt.figure(figsize=(8, 6))
        methods_list = list(method_averages.keys())
        averages = list(method_averages.values())
        
        # Δημιουργία μπάρας
        plt.bar(methods_list, averages, color=['blue', 'green', 'red'], width=0.5)
        
        # Προσαρμογή του y-άξονα για αρνητικές τιμές
        y_min = min(averages) * 1.2 if min(averages) < 0 else 0
        y_max = max(averages) * 1.2 if max(averages) > 0 else 0
        plt.ylim(y_min, y_max)
        
        # Προσαρμογές στο διάγραμμα
        plt.title(f"Μέσο ποσοστό μεταβολής αμβλείων για την κατηγορία: {cat}")
        plt.xlabel("Μέθοδος")
        plt.ylabel("Μέσο ποσοστό μεταβολής")
        plt.xticks(rotation=45)
        plt.grid(axis="y", linestyle="--", alpha=0.7)
        
        # Εμφάνιση του διαγράμματος
        plt.tight_layout()
        plt.show()


if __name__ == "__main__":
    energy_finding()
    #percentage_graph()
