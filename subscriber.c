#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subscriber.h"

#define MESSAGE_BOARD_FILE "message_board.txt"

// Publica a mensagem escrevendo no arquivo compartilhado
void publish(const char* topic_name, const char* message) {
    FILE* file = fopen(MESSAGE_BOARD_FILE, "a"); // "a" para append (adicionar ao final)
    if (file == NULL) {
        perror("Erro ao abrir o mural de mensagens");
        return;
    }
    fprintf(file, "%s:%s\n", topic_name, message);
    fclose(file);
    printf(">> Mensagem publicada com sucesso no mural.\n");
}

// Adiciona uma inscrição à lista local do peer
void subscribe(SubscriptionNode** head, const char* topic_name) {
    // Verifica se já está inscrito
    SubscriptionNode* current = *head;
    while (current != NULL) {
        if (strcmp(current->topic_name, topic_name) == 0) {
            printf(">> Voce ja esta inscrito no topico '%s'.\n", topic_name);
            return;
        }
        current = current->next;
    }

    // Cria e adiciona a nova inscrição
    SubscriptionNode* new_node = (SubscriptionNode*)malloc(sizeof(SubscriptionNode));
    new_node->topic_name = strdup(topic_name);
    new_node->next = *head;
    *head = new_node;
    printf(">> Inscrito com sucesso no topico '%s'.\n", topic_name);
}

// Remove uma inscrição da lista local do peer
void unsubscribe(SubscriptionNode** head, const char* topic_name) {
    SubscriptionNode* current = *head;
    SubscriptionNode* prev = NULL;

    while (current != NULL && strcmp(current->topic_name, topic_name) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf(">> Voce nao estava inscrito no topico '%s'.\n", topic_name);
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current->topic_name);
    free(current);
    printf(">> Inscricao em '%s' cancelada.\n", topic_name);
}

// Lê o mural e exibe as mensagens dos tópicos inscritos
void view_messages(SubscriptionNode* head, const char* peer_id) {
    printf("\n--- Mensagens para %s ---\n", peer_id);
    FILE* file = fopen(MESSAGE_BOARD_FILE, "r");
    if (file == NULL) {
        printf("Nenhuma mensagem no mural ainda.\n");
        return;
    }

    char line[512];
    int found_messages = 0;

    while (fgets(line, sizeof(line), file)) {
        char* topic = strtok(line, ":");
        char* message = strtok(NULL, "\n");

        if (topic && message) {
            SubscriptionNode* current_sub = head;
            while (current_sub != NULL) {
                if (strcmp(current_sub->topic_name, topic) == 0) {
                    printf("[%s]: %s\n", topic, message);
                    found_messages++;
                    break; 
                }
                current_sub = current_sub->next;
            }
        }
    }

    if (found_messages == 0) {
        printf("Nenhuma mensagem nova para os seus topicos.\n");
    }
    printf("--- Fim das Mensagens ---\n");
    fclose(file);
}

// Libera a memória da lista de inscrições
void cleanup_subscriptions(SubscriptionNode** head) {
    SubscriptionNode* current = *head;
    while (current != NULL) {
        SubscriptionNode* temp = current;
        current = current->next;
        free(temp->topic_name);
        free(temp);
    }
    *head = NULL;
}