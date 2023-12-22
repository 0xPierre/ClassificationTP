#include "Settings.h"

// Bonjour,
// Merci de descendre en dessous de la variable Args pour accéder aux différentes configurations possible et explications 
// La structure n'est pas faite pour être modifié manuellement par des personnes ne connaissant pas le projet.
DecisionArgs Args = {
	.split = SPLIT_NORMAL,
	.gini = GINI_NORMAL,
	.featureBaggingProportion = 1.f,
	.enableSigmoid = false,
	.useFeatureBagging = false,
	.useLocalFeatureBagging = false,
	.instanceBaggingProportion = 1.f,
	.useInstanceBagging = false,
	.isSilent = false,
	.prunningThreshold = 1.f,
	.treeCount = 1,
	.maxDepth = 30,
	.pathForest = "",
	.trainPath = NULL,
	.testPath = NULL,
	.filters = "\0",
	.filtersDatasets = false,
	.pathSaveForest = NULL,
	.useLoadForest = false,
	.saveForest = false,
	.isInVPL = false
};

/*
* Voici les différentes configurations permettant de tester notre travail.
* Chaque test peut posséder plusieurs paramètres.
*
* Nous n'avons fait aucun test avec le dataset FASHION. Nous nous sommes concentré sur les performances autour
* du dataset MNIST.
*
* /!\ IMPORTANT /!\
* un seul define principal doit être à true.
*/

// |
// | TEST BASE VPL
// |
// Ce test est seulement à utilisé pour tester le fonctionnement de VPL.
// Forêt de 100 arbres, avec bagging de features. Attention à ne pas lancer avec MNIST.
#define TEST_VPL_SIMPLE_FOREST_WITH_FEATURE_BAGGING true
// Merci de penser à le mettre à false avant de lancer un autre test.

// |
// | INTERFACE SDL
// |
// Pensez à activer le son !
#define RUN_SDL false
#define RUN_SDL_PATH_FOREST "../Forests/FOREST_TRAINED_FOR_SDL.dfm"

// |
// | TEST PENDIGITS
// |
// Ce test est fait pour être utilisé avec le dataset PENDIGITS.
#define TEST_PENDIGITS false
// Test PENDIGITS avec forêt.
#define TEST_PENDIGITS_WITH_FOREST true
// Nombre d'arbre dans la forêt
#define TEST_PENDIGITS_FOREST_TREE_COUNT 20
// Utilisation du bagging de feature. Ne pas mettre à true sans forêt
#define TEST_PENDIGITS_LOCAL_FEATURE_BAGGING false // Choisir un seul bagging parmis les 2
#define TEST_PENDIGITS_NORMAL_FEATURE_BAGGING false // Le bagging normal est meilleur sur PENDIGITS
#define TEST_PENDIGITS_NORMAL_FEATURE_BAGGING_PROPORTION 0.9f
// Test split amélioré | Ne marche pas sur VPL (segfault/"error"), seulement en local.
#define TEST_PENDIGITS_SPLIT_LESS_NODE false // Réduction du nombre de node de 35760 à 21654 pour 0.05 % de précision perdu
// Test Gini Entropy
#define TEST_PENDIGITS_GINI_ENTROPY false
// Prédiction en utilisant les sigmoids. Il faut mettre un seul arbre
#define TEST_PENDIGITS_ENABLE_SIGMOID false // Merci de désactiver le bagging
// Pour du test en local et non sur VPL, mettez false en dessous
#define TEST_PENDIGITS_IN_VPL true
// Score attendu : 
// Arbre simple sans bagging : 0.917
// Arbre simple sans bagging avec sigmoid : 0.92
// Forêt 50 arbres sans feature bagging : 0.957
// Forêt 50 arbres avec local feature bagging : 0.964
// Forêt 50 arbres avec feature bagging normal (0.9) : 0.966


// Merci de penser à mettre à false le premier define de pendigits avant de lancer un autre test.


// |
// | TEST MNIST
// |
// Ce test est fait pour être utilisé avec le dataset MNIST.
#define TEST_MNIST false
// Test MNIST avec forêt
#define TEST_MNIST_WITH_FOREST true
// Nombre d'arbre dans la forêt
// Nous vous recommandons grandement d'utiliser le bagging de feature pour un gain de temps conséquent.
// Défini à 10 arbres pour passer dans le temps imparti
// Pour profiter du meilleur rapport qualité/performance, il faut 20 arbres et être sur linux.
#define TEST_MNIST_FOREST_TREE_COUNT 10 // Vous pouvez essayer 20. Nous prenons un peu près 20 secondes sur notre pc.
// Utilisation du bagging de feature. Ne pas mettre à true sans forêt. Un seul bagging à true
#define TEST_MNIST_LOCAL_FEATURE_BAGGING true
#define TEST_MNIST_NORMAL_FEATURE_BAGGING false
#define TEST_MNIST_NORMAL_FEATURE_BAGGING_PROPORTION 0.9f
// Utilisation des filtres: filtrage de pixel et convolution.
#define TEST_MNIST_USE_FILTERS_CONVOLUTION true
// Pour du test en local et non sur VPL, mettez false en dessous
#define TEST_MNIST_IN_VPL true
// Score attendu : 
// Arbre simple sans rien : 0.861
// Forêt 20 arbres sans feature bagging : 0.928
// Forêt 20 arbres avec local feature bagging : 0.951
// Forêt 20 arbres avec local feature bagging et filtres/convolution : 0.982 ( 85 586 noeuds )
// Forêt 10 arbres avec local feature bagging et filtres/convolution : 0.976 ( 43 360 noeuds )
// Forêt 20 arbres avec feature bagging normal (0.9) : 0.979 ( 41 316 Noeuds )


// |
// | Enregistrement de Forêts
// | A tester en local
#define SAVE_FOREST false
#define SAVE_FOREST_TREE_COUNT 15 // Seulement 15 pour le test
#define SAVE_FOREST_PATH "SAVED_FOREST.dfm"
// Pour du test en local et non sur VPL, mettez false en dessous
#define TEST_SAVE_IN_VPL true


// |
// | Chargement d'une forêt
// | A tester en local
// | Car impossible de charger un fichier créé depuis un lancement fait avant.
#define LOAD_FOREST false
#define LOAD_FOREST_PATH "SAVED_FOREST.dfm"
// Pour du test en local et non sur VPL, mettez false en dessous
#define TEST_LOAD_IN_VPL true


// |
// | TEST Recherche d'hyper paramètres
// | Mieux à tester en local
// ATTENTION: Prévu SEULEMENT pour MNIST
// Si vous souhaitez modifier les paramètrs ) rechercher, vous pouvez aller dans HyperParamets.c 
// et modifier les valeurs minimal/maximal à partir de la ligne 24
#define TEST_HYPERPARAMETERS false
#define TEST_HYPERPARAMETERS_TREE_COUNT 3


// |
// | Test de notre meilleur forêt : 98.7 % de réussite
// | A tester en local
#define TEST_BEST_MNIST false
#define TEST_BEST_MNIST_FOREST_PATH "../Forests/MNIST_FILTERED_HYPERPARAMETERS_98_65.dfm"
// Merci de mettre les bons chemins pour les datasets
#define TEST_BEST_MNIST_TRAIN_PATH "../Datasets/MNIST_train.txt"
#define TEST_BEST_MNIST_TEST_PATH "../Datasets/MNIST_test.txt"

#if TEST_VPL_SIMPLE_FOREST_WITH_FEATURE_BAGGING
int main(int argc, char* args[]) {
	Args.isSilent = true;
	Args.isInVPL = true;
	Args.useLocalFeatureBagging = true;
	Args.treeCount = 100;

	strcpy(Args.trainPath, args[1]);
	strcpy(Args.testPath, args[2]);

	StartTest();

	return 0;
}
#endif

#if TEST_PENDIGITS
int main(int argc, char* args[]) {
	Args.isSilent = TEST_PENDIGITS_IN_VPL;
	Args.isInVPL = TEST_PENDIGITS_IN_VPL;


	if (TEST_PENDIGITS_WITH_FOREST) {
		Args.treeCount = TEST_PENDIGITS_FOREST_TREE_COUNT;
		if (!TEST_PENDIGITS_LOCAL_FEATURE_BAGGING) {
			Args.useFeatureBagging = TEST_PENDIGITS_NORMAL_FEATURE_BAGGING;
			Args.featureBaggingProportion = TEST_PENDIGITS_NORMAL_FEATURE_BAGGING_PROPORTION;
		}
		Args.useLocalFeatureBagging = TEST_PENDIGITS_LOCAL_FEATURE_BAGGING;
	}
	else {
		Args.treeCount = 1;
	}

	Args.enableSigmoid = TEST_PENDIGITS_ENABLE_SIGMOID;

	Args.split = TEST_PENDIGITS_SPLIT_LESS_NODE ? SPLIT_LESS_NODE : SPLIT_NORMAL;

	strcpy(Args.trainPath, args[1]);
	strcpy(Args.testPath, args[2]);

	StartTest();

	return 0;
}
#endif

#if TEST_MNIST
int main(int argc, char* args[]) {
	Args.isSilent = TEST_MNIST_IN_VPL;
	Args.isInVPL = TEST_MNIST_IN_VPL;

	if (TEST_MNIST_WITH_FOREST) {
		Args.treeCount = TEST_MNIST_FOREST_TREE_COUNT;
		if (TEST_MNIST_LOCAL_FEATURE_BAGGING) {
			Args.useLocalFeatureBagging = true;
		}
		else if (TEST_MNIST_NORMAL_FEATURE_BAGGING) {
			Args.useFeatureBagging = true;
			Args.featureBaggingProportion = TEST_MNIST_NORMAL_FEATURE_BAGGING_PROPORTION;
		}
	}
	else {
		Args.treeCount = 1;
	}

	Args.filtersDatasets = TEST_MNIST_USE_FILTERS_CONVOLUTION;
	Args.filters[0] = '0';
	Args.filters[1] = '1';

	strcpy(Args.trainPath, args[1]);
	strcpy(Args.testPath, args[2]);

	StartTest();
}
#endif

#if SAVE_FOREST
int main(int argc, char* args[]) {
	Args.isSilent = TEST_SAVE_IN_VPL;
	Args.isInVPL = TEST_SAVE_IN_VPL;

	Args.treeCount = SAVE_FOREST_TREE_COUNT;
	Args.useLocalFeatureBagging = true;

	strcpy(Args.pathSaveForest, SAVE_FOREST_PATH);
	strcpy(Args.trainPath, args[1]);
	strcpy(Args.testPath, args[2]);
	Args.saveForest = true;

	StartTest();
}
#endif

#if LOAD_FOREST
int main(int argc, char* args[]) {
	Args.isSilent = TEST_LOAD_IN_VPL;
	Args.isInVPL = TEST_LOAD_IN_VPL;

	strcpy(Args.pathForest, LOAD_FOREST_PATH);
	Args.useLoadForest = true;
	strcpy(Args.trainPath, args[1]);
	strcpy(Args.testPath, args[2]);
	StartTest();
}
#endif

#if TEST_HYPERPARAMETERS
int main(int argc, char* args[]) {
	printf("!!ONLY FOR MNIST!!\n");
	strcpy(Args.trainPath, args[1]);
	strcpy(Args.testPath, args[2]);
	Args.treeCount = TEST_HYPERPARAMETERS_TREE_COUNT;

	SearchHyperParametersOfRandomForest();
}
#endif

#if RUN_SDL
int main(int argc, char* argv[]) {
	RandomForest* rf = LoadForestFromFile(RUN_SDL_PATH_FOREST);
	RunSdl(rf);

	return 0;
}
#endif

#if TEST_BEST_MNIST
int main(int argc, char* argv[]) {
	Args.useLoadForest = true;
	strcpy(Args.pathForest, TEST_BEST_MNIST_FOREST_PATH);
	strcpy(Args.testPath, TEST_BEST_MNIST_TEST_PATH);
	strcpy(Args.trainPath, TEST_BEST_MNIST_TRAIN_PATH);

	Args.filtersDatasets = true;
	Args.filters[0] = '0';
	Args.filters[1] = '1';

	StartTest();

	return 0;
}
#endif