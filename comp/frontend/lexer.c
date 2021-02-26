/* lexer.c
 *
 * Tediously hand-written lexer for exercise purposes
 * using a labeled state-machine approach inspired by
 * re2c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "../helpers.h"

token_list_node_t* scan(lex_context& ctx);

token_list_t* lex(char* filename)
{
    token_list_t*      token_list = malloc(sizeof(token_list_t));
    token_list_node_t* begin_node = malloc(sizeof(token_list_node_t));

    begin_node->token = NULL;

    token_list->size = 0;
    token_list->begin = begin_node;

    token_list_node_t* pointer = begin_node;

    FILE* fp = fopen(filename, "r");

    while (1)
    {
        token_list_node_t* next_node = scan(fp);
        if (next_node->token->t_class == TOKEN_END) break;
        pointer->next = next_node;
        pointer = next_node;
        (token_list->size)++;
    }

    return token_list;
}

token_list_node_t* scan(lex_context& ctx)
{
    const char* anchor = ctx.cursor++;
    char* cc;
    switch (cc = *ctx.cursor)
    {
        // EOF
        case 0x00: goto lexend;

        // non-linebreak whitespace
        case 0x08:
        case '\t':
        case '\v':
        case '\f':
        case ' ':

        // linebreak whitespace
        case '\n':
        case '\r':

        // punctuators
        case '[':
        case ']':
        case '(':
        case ')':
        case '{':
        case '}':
        case '.':
        case '-':
        case '+':
        case '&':
        case '*':
        case '~':
        case '!':
        case '/':
        case '%':
        case '<':
        case '>':
        case '=':
        case '^':
        case '|':
        case '?':
        case ':':
        case ';':
        case ',':
        case '#':

        // numeric characters
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':

        // alphabetic characters
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case 'h':
        case 'j':
        case 'k':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'x':
        case 'y':
        case 'z':   goto key1;

        // keyword start characters
        case '_':   goto key27;
        case 'a':   goto key50;
        case 'b':   goto key66;
        case 'c':   goto key81;
        case 'd':   goto key89;
        case 'e':   goto key93;
        case 'f':   goto key94;
        case 'g':   goto key95;
        case 'i':   goto key96;
        case 'l':   goto key97;
        case 'r':   goto key98;
        case 's':   goto key99;
        case 't':   goto key100;
        case 'u':   goto key101;
        case 'v':   goto key102;
        case 'w':   goto key103;
        default:
    }

lexend:     return make_token(anchor, TOKEN_END);
key1:       cc = *++ctx.cursor;
lexid:      switch(cc)
            {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '_':
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'G':
                case 'H':
                case 'I':
                case 'J':
                case 'K':
                case 'L':
                case 'M':
                case 'N':
                case 'O':
                case 'P':
                case 'Q':
                case 'R':
                case 'S':
                case 'T':
                case 'U':
                case 'V':
                case 'W':
                case 'X':
                case 'Y':
                case 'Z':
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                case 'g':
                case 'h':
                case 'i':
                case 'j':
                case 'k':
                case 'l':
                case 'm':
                case 'n':
                case 'o':
                case 'p':
                case 'q':
                case 'r':
                case 's':
                case 't':
                case 'u':
                case 'v':
                case 'w':
                case 'x':
                case 'y':
                case 'z': goto key1;
                default: 
lexidsink:          return make_token(TOKEN_IDENTIFIER);
            }
key2:       switch ((cc = *++ctx.cursor))
            {
                case 'u': goto key30;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '_':
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'G':
                case 'H':
                case 'I':
                case 'J':
                case 'K':
                case 'L':
                case 'M':
                case 'N':
                case 'O':
                case 'P':
                case 'Q':
                case 'R':
                case 'S':
                case 'T':
                case 'U':
                case 'V':
                case 'W':
                case 'X':
                case 'Y':
                case 'Z':
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                case 'g':
                case 'h':
                case 'i':
                case 'j':
                case 'k':
                case 'l':
                case 'm':
                case 'n':
                case 'o':
                case 'p':
                case 'q':
                case 'r':
                case 's':
                case 't':
                case 'v':
                case 'w':
                case 'x':
                case 'y':
                case 'z': goto key1;
                default:  goto lexkeysink;
            }
key3:       if ((cc = *++ctx.cursor) == 's') goto key26;  else goto key1;
key4:       if ((cc = *++ctx.cursor) == 'u') goto key31;  else goto key1;
key5:       if ((cc = *++ctx.cursor) == 't') goto key32;  else goto key1;
key6:       if ((cc = *++ctx.cursor) == 'o') goto key33;  else goto key1;
key7:       if ((cc = *++ctx.cursor) == 't') goto key9;   else goto key1;
key8:       if ((cc = *++ctx.cursor) == 't') goto key24;  else goto key1;
key9:       switch (cc = *++ctx.cursor)
            {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '_':
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'G':
                case 'H':
                case 'I':
                case 'J':
                case 'K':
                case 'L':
                case 'M':
                case 'N':
                case 'O':
                case 'P':
                case 'Q':
                case 'R':
                case 'S':
                case 'T':
                case 'U':
                case 'V':
                case 'W':
                case 'X':
                case 'Y':
                case 'Z':
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                case 'g':
                case 'h':
                case 'i':
                case 'j':
                case 'k':
                case 'l':
                case 'm':
                case 'n':
                case 'o':
                case 'p':
                case 'q':
                case 'r':
                case 's':
                case 't':
                case 'u':
                case 'v':
                case 'w':
                case 'x':
                case 'y':
                case 'z': goto key1;
                default: 
lexkeysink:         return make_token(TOKEN_KEYWORD);
            }
key10:      if ((cc = *++ctx.cursor) == 't') goto key9;   else goto key1;
key11:      if ((cc = *++ctx.cursor) == 'n') goto key35;  else goto key1;
key12:      switch((cc = *++ctx.cursor))
            {
                case 'g':   goto key36;
                case 's':   goto key37;
                case 't':   goto key38;
                default:    goto key1;
            }
key13:      if ((cc = *++ctx.cursor) == 'o') goto key39;  else goto key1;
key14:      switch((cc = *++ctx.cursor))
            {
                case 'g':   goto key40;
                case 'z':   goto key41;
                default:    goto key1;
            }
key15:      switch((cc = *++ctx.cursor))
            {
                case 'a':   goto key42;
                case 'r':   goto key43;
                default:    goto key1;
            }
key16:      if ((cc = *++ctx.cursor) == 'i') goto key44;  else goto key1;
key17:      if ((cc = *++ctx.cursor) == 'p') goto key45;  else goto key1;
key18:      switch((cc = *++ctx.cursor))
            {
                case 'i':   goto key46;
                case 's':   goto key47;
                default:    goto key1;
            }
key19:      switch((cc = *++ctx.cursor))
            {
                case 'i':   goto key48;
                case 'l':   goto key49;
                default:    goto key1;
            }
key20:      if ((cc = *++ctx.cursor) == 'i') goto key51;  else goto key1;
key21:      if ((cc = *++ctx.cursor) == 'o') goto key52;  else goto key1;
key22:      if ((cc = *++ctx.cursor) == 'm') goto key53;  else goto key1;
key23:      if ((cc = *++ctx.cursor) == 'a') goto key54;  else goto key1;
key24:      if ((cc = *++ctx.cursor) == 'o') goto key9;   else goto key1;
key25:      if ((cc = *++ctx.cursor) == 'a') goto key55;  else goto key1;
key26:      if ((cc = *++ctx.cursor) == 'e') goto key9;   else goto key1;
key27:      switch((cc = *++ctx.cursor))
            {
                case 'B':   goto key104;
                case 'C':   goto key105;
                case 'I':   goto key106;
                default:    goto key1;
            }
key28:      switch((cc = *++ctx.cursor))
            {
                case 's':   goto key56;
                case 't':   goto key57;
                default:    goto key1;
            }
key29:      if ((cc = *++ctx.cursor) == 'a') goto key58;  else goto key1;
key30:      if ((cc = *++ctx.cursor) == 'b') goto key51;  else goto key1;
key31:      if ((cc = *++ctx.cursor) == 'm') goto key9;   else goto key1;
key32:      if ((cc = *++ctx.cursor) == 'e') goto key59;  else goto key1;
key33:      if ((cc = *++ctx.cursor) == 'e') goto key56;  else goto key1;
key34:      if ((cc = *++ctx.cursor) == 'i') goto key60;  else goto key1;
key35:      if ((cc = *++ctx.cursor) == 'g') goto key9;   else goto key1;
key36:      if ((cc = *++ctx.cursor) == 'i') goto key61;  else goto key1;
key37:      if ((cc = *++ctx.cursor) == 't') goto key62;  else goto key1;
key38:      if ((cc = *++ctx.cursor) == 'u') goto key59;  else goto key1;
key39:      if ((cc = *++ctx.cursor) == 'r') goto key56;  else goto key1;
key40:      if ((cc = *++ctx.cursor) == 'n') goto key63;  else goto key1;
key41:      if ((cc = *++ctx.cursor) == 'o') goto key64;  else goto key1;
key42:      if ((cc = *++ctx.cursor) == 't') goto key65;  else goto key1;
key43:      if ((cc = *++ctx.cursor) == 'u') goto key67;  else goto key1;
key44:      if ((cc = *++ctx.cursor) == 't') goto key68;  else goto key1;
key45:      if ((cc = *++ctx.cursor) == 'e') goto key69;  else goto key1;
key46:      if ((cc = *++ctx.cursor) == 'o') goto key70;  else goto key1;
key47:      if ((cc = *++ctx.cursor) == 'i') goto key71;  else goto key1;
key48:      if ((cc = *++ctx.cursor) == 'd') goto key9;   else goto key1;
key49:      if ((cc = *++ctx.cursor) == 'a') goto key72;  else goto key1;
key50:      if ((cc = *++ctx.cursor) == 'a') goto key8;   else goto key1;
key51:      if ((cc = *++ctx.cursor) == 'l') goto key26;  else goto key1;
key52:      if ((cc = *++ctx.cursor) == 'l') goto key9;   else goto key1;
key53:      if ((cc = *++ctx.cursor) == 'p') goto key73;  else goto key1;
key54:      if ((cc = *++ctx.cursor) == 'g') goto key74;  else goto key1;
key55:      if ((cc = *++ctx.cursor) == 'k') goto key9;   else goto key1;
key56:      if ((cc = *++ctx.cursor) == 't') goto key9;   else goto key1;
key57:      if ((cc = *++ctx.cursor) == 'i') goto key75;  else goto key1;
key58:      if ((cc = *++ctx.cursor) == 'u') goto key76;  else goto key1;
key59:      if ((cc = *++ctx.cursor) == 'r') goto key70;  else goto key1;
key60:      if ((cc = *++ctx.cursor) == 'n') goto key26;  else goto key1;
key61:      if ((cc = *++ctx.cursor) == 's') goto key77;  else goto key1;
key62:      if ((cc = *++ctx.cursor) == 'r') goto key78;  else goto key1;
key63:      if ((cc = *++ctx.cursor) == 'e') goto key48;  else goto key1;
key64:      if ((cc = *++ctx.cursor) == 'o') goto key79;  else goto key1;
key65:      if ((cc = *++ctx.cursor) == 'i') goto key80;  else goto key1;
key66:      if ((cc = *++ctx.cursor) == 'r') goto key107; else goto key1;
key67:      if ((cc = *++ctx.cursor) == 'c') goto key56;  else goto key1;
key68:      if ((cc = *++ctx.cursor) == 'c') goto key82;  else goto key1;
key69:      if ((cc = *++ctx.cursor) == 'd') goto key83;  else goto key1;
key70:      if ((cc = *++ctx.cursor) == 'n') goto key9;   else goto key1;
key71:      if ((cc = *++ctx.cursor) == 'g') goto key40;  else goto key1;
key72:      if ((cc = *++ctx.cursor) == 't') goto key20;  else goto key1;
key73:      if ((cc = *++ctx.cursor) == 'l') goto key84;  else goto key1;
key74:      if ((cc = *++ctx.cursor) == 'i') goto key85;  else goto key1;
key75:      if ((cc = *++ctx.cursor) == 'n') goto key86;  else goto key1;
key76:      if ((cc = *++ctx.cursor) == 'l') goto key56;  else goto key1;
key77:      if ((cc = *++ctx.cursor) == 't') goto key87;  else goto key1;
key78:      if ((cc = *++ctx.cursor) == 'i') goto key67;  else goto key1;
key79:      if ((cc = *++ctx.cursor) == 'f') goto key9;   else goto key1;
key80:      if ((cc = *++ctx.cursor) == 'c') goto key9;   else goto key1;
key81:      switch((cc = *++ctx.cursor))
            {
                case 'a':   goto key3;
                case 'h':   goto key108;
                case 'o':   goto key109;
                default:    goto key1;
            }
key82:      if ((cc = *++ctx.cursor) == 'h') goto key9;   else goto key1;
key83:      if ((cc = *++ctx.cursor) == 'e') goto key79;  else goto key1;
key84:      if ((cc = *++ctx.cursor) == 'e') goto key88;  else goto key1;
key85:      if ((cc = *++ctx.cursor) == 'n') goto key90;  else goto key1;
key86:      if ((cc = *++ctx.cursor) == 'u') goto key26;  else goto key1;
key87:      if ((cc = *++ctx.cursor) == 'e') goto key7;   else goto key1;
key88:      if ((cc = *++ctx.cursor) == 'x') goto key9;   else goto key1;
key89:      switch((cc = *++ctx.cursor))
            {
                case 'e':   goto key110;
                case 'o':   goto key2;
                default:    goto key1;
            }
key90:      if ((cc = *++ctx.cursor) == 'a') goto key91;  else goto key1;
key91:      if ((cc = *++ctx.cursor) == 'r') goto key92;  else goto key1;
key92:      if ((cc = *++ctx.cursor) == 'y') goto key9;   else goto key1;
key93:      switch((cc = *++ctx.cursor))
            {
                case 'l':   goto key3;
                case 'n':   goto key4;
                case 'x':   goto key5;
                default:    goto key1;
            }
key94:      switch((cc = *++ctx.cursor))
            {
                case 'l':   goto key6;
                case 'o':   goto key7;
                default:    goto key1;
            }
key95:      if ((cc = *++ctx.cursor) == 'o') goto key8;   else goto key1;
key96:      switch((cc = *++ctx.cursor))
            {
                case 'f':   goto key9;
                case 'n':   goto key10;
                default:    goto key1;
            }
key97:      if ((cc = *++ctx.cursor) == 'o') goto key11;   else goto key1;
key98:      if ((cc = *++ctx.cursor) == 'e') goto key12;   else goto key1;
key99:      switch((cc = *++ctx.cursor))
            {
                case 'h':   goto key13;
                case 'i':   goto key14;
                case 't':   goto key15;
                case 'w':   goto key16;
                default:    goto key1;
            }
key100:     if ((cc = *++ctx.cursor) == 'y') goto key17;   else goto key1;
key101:     if ((cc = *++ctx.cursor) == 'n') goto key18;   else goto key1;
key102:     if ((cc = *++ctx.cursor) == 'o') goto key19;   else goto key1;
key103:     if ((cc = *++ctx.cursor) == 'h') goto key20;   else goto key1;
key104:     if ((cc = *++ctx.cursor) == 'o') goto key21;   else goto key1;
key105:     if ((cc = *++ctx.cursor) == 'o') goto key22;   else goto key1;
key106:     if ((cc = *++ctx.cursor) == 'm') goto key23;   else goto key1;
key107:     if ((cc = *++ctx.cursor) == 'e') goto key25;   else goto key1;
key108:     if ((cc = *++ctx.cursor) == 'a') goto key7;    else goto key1;
key109:     if ((cc = *++ctx.cursor) == 'n') goto key28;   else goto key1;
key110:     if ((cc = *++ctx.cursor) == 'f') goto key29;   else goto key1;
}
