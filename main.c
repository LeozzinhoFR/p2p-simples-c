#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subscriber.h"

void print_menu() {
    printf("\n--- Peer P2P ---\n");
    printf("1. Publicar mensagem\n");
    printf("2. Inscrever-se em um topico\n");
    printf("3. Cancelar inscricao\n");
    printf("4. Ver minhas mensagens\n"); // Nova opção
    printf("5. Sair\n");
    printf(">> Escolha uma opcao: ");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nome_do_peer>\n", argv[0]);
        return 1;
    }
    char* peer_name = argv[1];

    // Cada peer agora tem sua própria lista de inscrições
    SubscriptionNode* my_subscriptions = NULL;

    printf("Bem-vindo, Peer '%s'!\n", peer_name);

    // Simulação inicial para teste
    if (strcmp(peer_name, "PeerA") == 0) {
        subscribe(&my_subscriptions, "Esportes");
    }
    if (strcmp(peer_name, "PeerB") == 0) {
        subscribe(&my_subscriptions, "Musica");
    }

    int choice;
    char topic_buffer[100];
    char message_buffer[256];

    do {
        print_menu();
        scanf("%d", &choice);
        while (getchar() != '\n'); // Limpa o buffer de entrada

        switch (choice) {
            case 1:
                printf("Digite o topico para publicar: ");
                fgets(topic_buffer, sizeof(topic_buffer), stdin);
                topic_buffer[strcspn(topic_buffer, "\n")] = 0;

                printf("Digite a mensagem: ");
                fgets(message_buffer, sizeof(message_buffer), stdin);
                message_buffer[strcspn(message_buffer, "\n")] = 0;

                publish(topic_buffer, message_buffer);
                break;
            case 2:
                printf("Digite o topico para se inscrever: ");
                fgets(topic_buffer, sizeof(topic_buffer), stdin);
                topic_buffer[strcspn(topic_buffer, "\n")] = 0;
                subscribe(&my_subscriptions, topic_buffer);
                break;
            case 3:
                printf("Digite o topico para cancelar a inscricao: ");
                fgets(topic_buffer, sizeof(topic_buffer), stdin);
                topic_buffer[strcspn(topic_buffer, "\n")] = 0;
                unsubscribe(&my_subscriptions, topic_buffer);
                break;
            case 4:
                view_messages(my_subscriptions, peer_name);
                break;
            case 5:
                printf("Encerrando peer '%s'...\n", peer_name);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (choice != 5);

    cleanup_subscriptions(&my_subscriptions);

    return 0;
}