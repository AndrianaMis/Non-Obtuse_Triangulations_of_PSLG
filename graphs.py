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
avg_avg={}

# Άνοιγμα του αρχείου και ανάγνωση
for cat , instaces in categories.items():
    sum_avg_pn = {method: 0 for method in methods}
    count = {method: 0 for method in methods}
    for method in methods:
        for i, inst in enumerate(instaces):
            print(f'i: {i+1}, method: {method}, category: {cat}')
            with open('.vscode/results/results_{cat}_{i+1}_{method}.txt', 'r') as file:
                lines = file.readlines()

                for line in lines:
                    if line.startswith("Μέσος ρυθμός σύγκλισης:"):  # Αν η γραμμή ξεκινάει με 'pn:', τότε έχουμε δεδομένα
                        # Διαχωρισμός των τιμών της γραμμής
                        parts = line.split()
                        avg_pn = float(parts[0].split(":")[1])  # Παίρνουμε την τιμή του pn
                        sum_avg_pn[method] += avg_pn
                        count[method] += 1
    avg_avg[cat] = {method: (sum_avg_pn[method] / count[method] if count[method] > 0 else 0) for method in methods}




categories_list = list(avg_avg.keys())
x = range(len(categories_list))

for method in methods:
    averages = [avg_avg[cat][method] for cat in categories_list]
    plt.bar(
        [pos + 0.2 * methods.index(method) for pos in x],  # Θέση μπάρας
        averages,
        width=0.2,
        label=method,
    )

# Προσαρμογές στο διάγραμμα
plt.xticks([pos + 0.3 for pos in x], categories_list)  # Τοποθέτηση κατηγοριών στον x-άξονα
plt.xlabel("Κατηγορία")
plt.ylabel("Μέσος ρυθμός σύγκλισης")
plt.title("Μέσος ρυθμός σύγκλισης ανά κατηγορία και μέθοδο")
plt.legend()
plt.show()