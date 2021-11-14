ΚΑΡΛΗΣ ΝΙΚΟΛΑΟΣ 1115201800068
ΧΑΤΖΗΠΑΥΛΟΥ ΜΑΡΙΑ 1115201400223


./clustering -i input_small_id -o output_file -c cluster.conf -m LSH -o2
./clustering -i input_small_id -o output_file -c cluster.conf -m Hypercube -o2
./clustering -i input_small_id -o output_file -c cluster.conf -m Classic -o2

Η silhouette παιρνει πάρα πολύ χρόνο αλλά βγαζει αποτέλεσμα για αυτό το εμφανίζουμε τελευταίο.

Διαβάζουμε τα ορίσματα που δίνονται και το αρχείο config.

To initialization++ γίνεται ακριβώς όπως λέει στις διαφάνειες 45-46.

Στο hypercube αποθηκεύω για κάθε centroid τα gp/buckets που του αντιστοιχούν για να μην τα υπολογίζουμε συνέχεια.
Γίνεται το reverse assignment όπως μας ζητάτε.
Όσα point γίνονται assign τα κάνουμε mark για να μην ξαναγίνουν.

Για να μην χρησιμοποιώ δείκτες έκανε την εξής πατέντα: έχω ένα πεδίο index στα dPoint που αντιστοιχεί,τα point που έχω βάλει στο hashtable/cube με το dataset (την θέση i στο dataset) και έτσι τα κάνω mark και δεν τα ξαναελέχω. 

Στο hypercube είναι πολύ παρόμοιο με το lsh.