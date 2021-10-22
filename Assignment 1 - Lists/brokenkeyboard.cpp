/**
 * Except where otherwise noted, the following code is licensed under the Creative Commons Attribution 4.0 International license (CC BY 4.0):
 * http://creativecommons.org/licenses/by/4.0/
 * Copyright 2021 Gabriel Vieira
 * https://github.com/gqmv
 *
 * Whenever using, citing, or modifying this work, be sure to include a copy of the license and this notice.
 */

#include <iostream>

using namespace std;

const char homekey = '[';
const char endkey = ']';

/**
 * A keyboard interface that supports keypresses, including homekey and endkey.
 */
class KeyboardInterface
{
private:
    /**
     * The implementation of the keyboard interface uses a LinkedList to store the keypresses.
     * This is then abstracted from the user by keeping all low level methods private.
     */

    struct Node
    {
        char data;
        Node *next;
        Node(char data)
        {
            this->data = data;
            this->next = nullptr;
        }
    };

    Node *head;
    Node *tail;
    Node *cursor;
    int textSize;

    void insert_head(char data)
    {
        Node *new_node = new Node(data);
        new_node->next = head;
        head = new_node;
        if (textSize == 0)
        {
            tail = new_node;
        }
        textSize++;
        cursor = new_node;
    }

    void insert(char data)
    {
        Node *new_node = new Node(data);
        if (this->cursor == nullptr)
        {
            insert_head(data);
        }
        else
        {
            new_node->next = cursor->next;
            cursor->next = new_node;
            if (new_node->next == nullptr)
            {
                tail = new_node;
            }
            textSize++;
            cursor = new_node;
        }
    }

    char getFirstChar()
    {
        char data = this->head->data;
        Node *temp = this->head;
        this->head = this->head->next;
        delete temp;
        this->textSize--;
        return data;
    }

public:
    KeyboardInterface(const char homekey, const char endkey)
    {
        const char homekey = homekey;
        const char endkey = endkey;

        this->head = nullptr;
        this->tail = nullptr;
        this->cursor = nullptr;
        this->textSize = 0;
    }

    /**
     * Gets the size of the text stored at the keyboard interface's memory.
     *
     * @return the size of the text stored at the keyboard interface's memory.
     */
    int getTextSize()
    {
        return this->textSize;
    }

    /**
     * Records a keypress from the keyboard. This keypress can be a normal character or a special key.
     * If the keypress is a special key, the cursor is moved to the appropriate position.
     * Otherwise, the keypress is inserted at the cursor position.
     *
     * @param data the character to be inserted.
     */
    void registerKeypress(char data)
    {
        if (data == homekey)
        {
            this->cursor = nullptr;
            return;
        }
        if (data == endkey)
        {
            this->cursor = this->tail;
            return;
        }

        this->insert(data);
    }

    /**
     * Returns the text that has been typed so far and deletes it from the keyboard interface's memory.
     *
     * @return the text that has been typed so far.
     */
    string getText()
    {
        string text = "";
        Node *temp = this->head;
        while (temp != nullptr)
        {
            text += temp->data;
            temp = temp->next;
        }
        return text;
    }
};

int main()
{
    string input;

    while (getline(cin, input))
    {
        KeyboardInterface keyboard(homekey, endkey);
        for (int i = 0; i < input.size(); i++)
        {
            keyboard.registerKeypress(input[i]);
        }

        cout << keyboard.getText() << endl;
    }
}
