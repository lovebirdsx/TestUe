module.exports = {
    root: true,
    parser: '@typescript-eslint/parser',
    parserOptions: {
        sourceType: 'module',
    },
    env: {
        jest: true,
        node: true,
    },
    plugins: ['@typescript-eslint/eslint-plugin'],
    extends: ['airbnb-base', 'plugin:@typescript-eslint/recommended', 'plugin:prettier/recommended'],
    settings: {
        'import/resolver': {
            node: {
                extensions: ['.js', '.jsx', '.ts', '.tsx'],
            },
        },
        'import/core-modules': ['electronAPI'], // 让eslint认识electronAPI, 避免报错
    },
    rules: {
        'import/extensions': [
            'error',
            'ignorePackages',
            {
                js: 'never',
                jsx: 'never',
                ts: 'never',
                tsx: 'never',
            },
        ],
        'object-curly-newline': [
            'error',
            {
                ObjectPattern: {
                    multiline: true,
                },
                ImportDeclaration: {
                    consistent: true,
                    multiline: true,
                },
                ExportDeclaration: {
                    multiline: true,
                    minProperties: 3,
                },
            },
        ],
        'import/no-extraneous-dependencies': [
            'error',
            {
                packageDir: `${__dirname}/..`,
            },
        ],
        'linebreak-style': 'off',
        'no-plusplus': 'off',
        'no-console': 'error',
        'no-shadow': 'off',
        'no-redeclare': 'off',
        'no-param-reassign': [
            'error',
            {
                props: false,
            },
        ],
        indent: 'off',
        'import/prefer-default-export': 'off',
        'lines-between-class-members': 'off',
        'no-restricted-syntax': 'off',
        'guard-for-in': 'off',
        'no-useless-constructor': 'off',
        'no-unused-vars': 'off',
        'no-empty-function': 'off',
        'no-inner-declarations': 'off',
        'max-classes-per-file': 'off',
        'class-methods-use-this': 'off',
        '@typescript-eslint/no-non-null-assertion': 'off',
        '@typescript-eslint/no-empty-function': 'off',
        'max-len': 'off',
        'no-await-in-loop': 'off',
        '@typescript-eslint/no-unused-vars': [
            'error',
            {
                ignoreRestSiblings: true,
                argsIgnorePattern: '^_',
                varsIgnorePattern: '^(memoize)$',
            },
        ],
    },
};
